#include <stdio.h>
#include "linkedlist.h"

void ll_init(LinkedList* list) {
    list->head_offset = OFFSET_NULL;
}

int ll_insert_last(Arena* arena, LinkedList* list, int value) {
    //book tempat di arena untuk node baru
    size_t new_node_offset = arena_alloc(arena, sizeof(LLNode));
    if (new_node_offset == (size_t)-1) return 0; // gagal alokasi

    LLNode* new_node = (LLNode*)arena_get(arena, new_node_offset);
    new_node->data = value;
    new_node->next_offset = OFFSET_NULL; //node baru jadi yang terakhir

    //list kosong = jadiin node baru sebagai head
    if (list->head_offset == OFFSET_NULL) {
        list->head_offset = new_node_offset;
        return 1;
    }

    //jika tidak kosong, cari sampe akhir
    LLNode* current = (LLNode*)arena_get(arena, list->head_offset);
    while (current->next_offset != OFFSET_NULL) {
        //offset selanjutnya jd pointer
        current = (LLNode*)arena_get(arena, current->next_offset);
    }

    //nyambung node terakir sm node baru (pake angka offset)
    current->next_offset = new_node_offset;
    return 1;
}

//view all linkedlist
void ll_print(Arena* arena, LinkedList* list) {
    printf("Isi Linked List: ");
    if (list->head_offset == OFFSET_NULL) {
        printf("[Kosong]\n");
        return;
    }

    size_t current_offset = list->head_offset;
    while (current_offset != OFFSET_NULL) {
        LLNode* current = (LLNode*)arena_get(arena, current_offset);
        printf("[%d (offset:%zu)] -> ", current->data, current_offset);
        current_offset = current->next_offset;
    }
    printf("NULL\n");
}