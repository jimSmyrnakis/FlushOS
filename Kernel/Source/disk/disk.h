#ifndef __FLUSHOS_DISK_H__
#define __FLUSHOS_DISK_H__
    /**
 * @file disk.h
 * @author Δημήτρης Σμυρνάκης (you@domain.com)
 * @brief Εδώ είναι ο διαχειρίστης δίσκων . Είναι υπεύθυνος ώστε κάθε νέα προσθήκη 
 * δίσκου να γίνεται αναζήτηση μέσα απο το σύστημα άρχειων για άν τεριάζει το format
 * του . Μέλλοντικα είναι επίσης εύκολο να πρόσθεθη και partitioning δύνατοτητα με πάρομοιο
 * τρόπο περίπου με αυτό του συστήματος άρχειων .
 * @version 0.1
 * @date 2026-07-20
 * 
 * @copyright Copyright (c) 2026 
 * 
 */
    

    #include <stdint-gcc.h>
    #include <stddef.h>
    
    #include "../errno.h"
    

    struct disk_attributes{
        uint32_t sector_length;
        uint32_t zero;
        uint64_t sector_count;
        uint64_t lba_base;
        
    }__attribute__((packed));
    typedef struct disk_attributes disk_attributes;

    typedef errno (*disk_read_proc)(uint64_t lba, uint32_t total, void* buffer , void* priv);
    
    typedef errno (*disk_write_proc)(uint64_t lba , uint32_t total, void* buffer , void* priv);
    
    
    struct file_system;

    

    struct disk_module{
        disk_read_proc          read;
        disk_write_proc         write;
    }__attribute__((packed));

    typedef struct disk_module disk_module;

    struct disk{
        struct disk_attributes  attrs;
        struct disk_module      module;
        struct file_system*     fs;
        uint32_t                id;
        void*                   priv; 
        
    };
    typedef struct disk disk;

    /**
     * @brief Εδώ έχουμε την αρχίκοποιηση της διαχείρισης δίσκων .
     * Αν και προς στιγμην απλός μηδενιζει πινακες και οριζει αρχικη συμπεριφορα 
     * μελλοντικα ισώς χρειάστει και για παράπανω πράγματα . 
     * 
     */
    void disk_init(void);

    /**
     * @brief Όταν θέλουμε να δήμιουργήσουμε έναν νέο δίσκο απλός περνάμε
     * τα βασικά στοιχεία όπως σύναρτήσεις προσπέλασης του αλλά και τις 
     * ίδιότητες του και κρύφα δέδομενα που χρειάζεται ο δίσκος κατά τις
     * προσπέλασεις . Επίσης η σύναρτηση αυτή είναι υπεύθυνη να καλέσει το 
     * σύστημα αρχείων για να βρέθει αν το format του δίσκου μπορεί να διαβάστη
     * απο κάποιο υπάρχτο σύστημα αρχείων . 
     * 
     * @param module Περιέχει όλες τις βασικές σύναρτησεις προσπέλασης του δίσκου .
     * @param priv Δεδομένα που πρέπει ανα προσπέλαση να περνουν οι σύναρτησεις 
     * πρόσπελασης του module . 
     * @param attrs Περιέχει το μέγεθος σε bytes του disk sector , το πλήθος
     * sectors και την διεύθυνση βάσης σε sector μοναδες . 
     * @return errno Επίτρέφει FLUSHOS_EGOOD άν όλα πάνε μια χάρα ,
     * FLUSHOS_ΕBADARGS αν το module είναι null ,
     * FLUSHOS_EBADDISK άν δεν υπάρχει μία απο τις βασικές σύναρτησεις ,
     * FLUSHOS_EOOB άν δεν μπορέσει να πρόσθεση νέο δίσκο .
     * 
     */
    errno disk_create(
        struct disk_module* module , 
        void* priv , struct disk_attributes attrs);
    
    /**
     * @brief Επιστρέφει μια δόμη δίσκου αν φύσικα είναι υπάρχτος . Το
     * index πρεπει να είναι θέση υπάρχτου δίσκου . Αυτο χρήσιμοποιήται
     * για debugging ποιο πολλή .
     * 
     * @param index 
     * @return struct disk* NULL αν δεν βρέθει η δομή δίσκου αν βρέθει .
     */
    struct disk* disk_get(int index);

    /**
     * @brief 
     * 
     * @param idisk 
     * @return errno 
     */
    errno disk_destroy(struct disk* idisk);

    errno disk_read( struct disk* idisk , uint64_t lba , uint32_t total , void* buffer );
    
    errno disk_write( struct disk* idisk , uint64_t lba , uint32_t total , void* buffer);



    
    uint32_t disk_get_id(struct disk* idisk);

    uint16_t disk_get_max_disks(void);
    
    uint16_t disk_get_disks_count(void);
    

    
#endif 