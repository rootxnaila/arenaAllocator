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
    size_t head_offset; // arak ke node pertama
} LinkedList;

void ll_init(LinkedList* list);
int ll_insert_last(Arena* arena, LinkedList* list, int value);
void ll_print(Arena* arena, LinkedList* list);

#endif