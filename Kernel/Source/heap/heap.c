#include "heap.h"
#include "../std/memory.h"
// flags
#define HAS_NEXT        ((uint8_t)0x80)
#define IS_FIRST        ((uint8_t)0x40)
#define SYSTEM_BLOCK    ((uint8_t)0x20)
#define ET3             ((uint8_t)0x08)
#define ET2             ((uint8_t)0x04)
#define ET1             ((uint8_t)0x02)
#define BLOCK_TAKEN     ((uint8_t)0x01)
#define FREE_BLOCK      ((uint8_t)0x00)

#ifndef NULL
#define NULL ((void*)0)
#endif

#define FLUSHOS_EBADBLOCKSIZE 10
#define FLUSHOS_EBADBLOCKCONT 11
#define FLUSHOS_EBADSIZE      12


#define MIN_BLOCK_SIZE 128
#define MIN_BLOCK_COUNT 2
// align_up: ασφαλές, χωρίς διπλό modulo
static inline uiptr align_up(uiptr base , uint16_t align){
    if (align == 0) return base;
    uiptr offset = base % align;
    if (offset != 0) base += (align - offset);
    return base;
}

/* heap_create: διορθωμένο, ασφαλές, 1 byte/entry table */
errno heap_create(struct heap_attr attr , struct heap** heap){
    struct heap * newHeap = NULL;
    *heap = NULL;
    
    uiptr base = attr.base;
    uiptr size = attr.size;
    uint16_t block_size = attr.block_size;

    if (block_size < MIN_BLOCK_SIZE)
        return FLUSHOS_EBADBLOCKSIZE;

    // total blocks that fit in region
    uint32_t total_blocks = size / block_size;
    if (total_blocks < MIN_BLOCK_COUNT)
        return FLUSHOS_EBADBLOCKCONT;

    // place structs aligned
    uiptr heap_struct_base = align_up(base , (uint16_t)sizeof(struct heap));
    uiptr info_struct_base = align_up(heap_struct_base + sizeof(struct heap),
                                      (uint16_t)sizeof(struct heap_info));

    // heap table: 1 byte per block (simple implementation)
    uiptr heap_table_base = info_struct_base + sizeof(struct heap_info);
    uint32_t table_entries = total_blocks; // bytes

    // where user heap will start (align to block_size)
    uiptr user_heap_base = align_up(heap_table_base + table_entries, block_size);

    // sanity check: user_heap_base within region
    if (user_heap_base < base) return FLUSHOS_EBADSIZE;
    if ((user_heap_base - base) > size) return FLUSHOS_EBADSIZE;

    // compute system blocks consumed by structs+table
    uint32_t system_blocks = (user_heap_base - base) / block_size;
    if (system_blocks == 0) system_blocks = 1; // enforce at least 1 

    if (system_blocks > total_blocks) return FLUSHOS_EBADSIZE;

    uint32_t user_blocks = total_blocks - system_blocks;
    if (user_blocks == 0) return FLUSHOS_EBADSIZE;

    // fill structures
    newHeap = (struct heap*)heap_struct_base;
    newHeap->info = (struct heap_info*)info_struct_base;
    newHeap->sys_data = (void*)heap_table_base;

    newHeap->info->base = base;
    newHeap->info->size = size;
    newHeap->info->blck_size = block_size;

    newHeap->info->heap_base = user_heap_base;
    newHeap->info->heap_size = user_blocks * block_size;
    newHeap->info->heap_blks = (uint32_t)user_blocks;

    newHeap->info->syst_base = base;
    newHeap->info->syst_size = system_blocks * block_size;
    newHeap->info->syst_blks = (uint32_t)system_blocks;

    newHeap->info->avai_blks = (uint32_t)user_blocks;

    // initialize table (cast to uint8_t*)
    uint8_t *table = (uint8_t*) newHeap->sys_data;

    // mark system blocks
    if (system_blocks > 0) {
        memset(table, SYSTEM_BLOCK, system_blocks);
    }
    // mark user blocks as free
    if (user_blocks > 0) {
        memset(table + system_blocks, FREE_BLOCK, user_blocks);
    }

    *heap = newHeap;
    return FLUSHOS_EGOOD;
}

/* heap_get_info unchanged */
struct heap_info heap_get_info(struct heap* id){
    return *(id->info);
}

static inline bool isBlockFree(uint8_t entry){
    return !(entry & BLOCK_TAKEN) && !(entry & SYSTEM_BLOCK);
}

/* heap_malloc: corrected */
void* heap_malloc(struct heap* id , size_t size){
    if (!id || size == 0) return NULL;

    uint8_t* table = (uint8_t*) id->sys_data;
    uint32_t block_size = id->info->blck_size;

    uint32_t system_blocks = id->info->syst_blks;
    uint32_t user_blocks = id->info->heap_blks;
    uint32_t total_blocks = system_blocks + user_blocks;

    // ceil division: blocks needed
    uint32_t blocks_needed = (size + block_size - 1) / block_size;
    if (blocks_needed == 0 || blocks_needed > user_blocks) return NULL;

    uint32_t start = system_blocks;
    uint32_t end_exclusive = system_blocks + user_blocks; // exclusive bound

    for (uint32_t i = start; i + blocks_needed <= end_exclusive; ++i){
        // quick skip
        if (!isBlockFree(table[i])) continue;

        bool ok = true;
        for (uint32_t j = 0; j < blocks_needed; ++j){
            if (!isBlockFree(table[i + j])) { ok = false; break; }
        }
        if (!ok) continue;

        // allocate
        for (uint32_t j = 0; j < blocks_needed; ++j){
            uint8_t flags = BLOCK_TAKEN;
            if (j == 0) flags |= IS_FIRST;
            if (j + 1 < blocks_needed) flags |= HAS_NEXT;
            table[i + j] = flags;
        }

        // compute pointer to returned memory
        uiptr offset_blocks = i - system_blocks; // 0-based within user area
        uiptr ptr = id->info->heap_base + offset_blocks * block_size;

        // update available
        id->info->avai_blks -= blocks_needed;

        return (void*)ptr;
    }

    // not found
    return NULL;
}

/* heap_zalloc: zero full allocated blocks (not only requested bytes),
   so the entire returned block area is zeroed */
void* heap_zalloc(struct heap* id , size_t size){
    if (!id || size == 0) return NULL;
    uint32_t block_size = id->info->blck_size;
    uint32_t blocks_needed = (size + block_size - 1) / block_size;

    void* p = heap_malloc(id, size);
    if (!p) return NULL;

    // zero exactly blocks_needed * block_size (safe)
    memset(p, 0, blocks_needed * block_size);
    return p;
}

/* heap_free: corrected */
bool heap_free(struct heap* id , void* ptr){
    if (!id || !ptr) return false;

    uiptr uptr = (uiptr)ptr;
    uiptr hbase = id->info->heap_base;
    uiptr hsize = id->info->heap_size;
    uint32_t block_size = id->info->blck_size;

    // check bounds
    if ((uptr < hbase) || (uptr >= (hbase + hsize))) return false;

    // find block index relative to user heap
    uint32_t offset = uptr - hbase;
    uint32_t block_index_in_user = offset / block_size; // floor
    uint32_t index = block_index_in_user + id->info->syst_blks; // absolute table index

    uint8_t *table = (uint8_t*) id->sys_data;

    // must be taken and IS_FIRST
    if (!(table[index] & BLOCK_TAKEN)) return false;
    if (!(table[index] & IS_FIRST)) {
        // pointer not at start of allocation
        return false;
    }

    // walk and free following blocks until no HAS_NEXT
    uint32_t i = index;
    uint32_t freed = 0;
    while (i < (id->info->syst_blks + id->info->heap_blks)){
        uint8_t ent = table[i];
        if (!(ent & BLOCK_TAKEN)) break; // inconsistency -> stop
        // clear entry
        table[i] = FREE_BLOCK;
        freed++;
        if (ent & HAS_NEXT){
            i++;
            continue;
        } else {
            break;
        }
    }

    // update available count
    id->info->avai_blks += freed;
    return true;
}
