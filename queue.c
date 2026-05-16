#include <stdio.h>
#include <string.h>
#include "queue.h"

// init antrean kosong dengan mengatur nilai head dan tail ke offset null
void queue_init(Queue* q) {
    q->head_offset = OFFSET_NULL;
    q->tail_offset = OFFSET_NULL;
}

// memeriksa apakah antrean sedang dalam keadaan kosong berdasarkan posisi head
int is_empty(Queue* q) { //antrean kosong?
    return q->head_offset == OFFSET_NULL;
}

// menyisipkan data teks ke belakang antrean n minta ruang dari arena 
int enqueue(Arena* arena, Queue* q, const char* message) {
    //minta tempat di arena
    size_t new_node_offset = arena_alloc(arena, sizeof(QueueNode));
    if (new_node_offset == (size_t)-1) return 0; //arena full!

    QueueNode* new_node = (QueueNode*)arena_get(arena, new_node_offset);
    strncpy(new_node->message, message, 127);
    new_node->message[127] = '\0'; //makesure string aman
    new_node->next_offset = OFFSET_NULL;

    if (is_empty(q)) {
        q->head_offset = new_node_offset;
        q->tail_offset = new_node_offset;
    } else {
        QueueNode* tail_node = (QueueNode*)arena_get(arena, q->tail_offset);
        tail_node->next_offset = new_node_offset;
        q->tail_offset = new_node_offset;
    }
    return 1;
}

// mengeluarkan data terdepan dari antrean dengan menggeser head offset tanpa memanggil fungsi free
int dequeue(Arena* arena, Queue* q, char* out_message) {
    if (is_empty(q)) return 0; 

    QueueNode* head_node = (QueueNode*)arena_get(arena, q->head_offset);
    
    if (out_message) {
        strcpy(out_message, head_node->message);
    }

    q->head_offset = head_node->next_offset;

    if (q->head_offset == OFFSET_NULL) {
        q->tail_offset = OFFSET_NULL; 
    }

    return 1;
}