#ifndef QUEUE_H
#define QUEUE_H

#include "arena.h"
#include "linkedlist.h" //buat offset null

typedef struct { //node queue menyimpan teks
    char message[128]; //nyimpen teks log dataset 
    size_t next_offset; //pointer relatif ke data selanjutnya
} QueueNode;

typedef struct { //struktur antrean (need head dan tail agar enqueue O(1))
    size_t head_offset;
    size_t tail_offset;
} Queue;

void queue_init(Queue* q);
int enqueue(Arena* arena, Queue* q, const char* message);
int dequeue(Arena* arena, Queue* q, char* out_message);
int is_empty(Queue* q);

#endif