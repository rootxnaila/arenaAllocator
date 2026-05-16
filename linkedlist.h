#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "arena.h"

//const null offset
#define OFFSET_NULL ((size_t)-1)

typedef struct {
    int data;          
    size_t next_offset; //integer jarak ke elemen berikutnya
} LLNode;

//struct untuk head linked list
typedef struct {
    size_t head_offset; //jarak ke node pertama
} LinkedList;

void ll_init(LinkedList* list); // init linked list menjadi kosong dengan mengatur head offset ke null
int ll_insert_last(Arena* arena, LinkedList* list, int value); // nambah node baru dengan nilai tertentu di posisi paling belakang linked list
void ll_print(Arena* arena, LinkedList* list); // cetak seluruh elemen di dalam linked list n menelusuri data antar offset

#endif