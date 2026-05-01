#include <stdio.h>
#include "arena.h"
#include "array.h"
#include "linkedlist.h"

int main() {
    printf("DEMO ARENA ALLOCATOR (progress week 2) ===\n");
    //book arena
    Arena* my_arena = arena_create(100);
    
    printf("\n---Try On Array---\n");
    size_t arr_len = 5;
    size_t my_array_offset = array_create(my_arena, arr_len);
    
    //isi array
    array_set(my_arena, my_array_offset, 0, 10);
    array_set(my_arena, my_array_offset, 1, 20);
    array_set(my_arena, my_array_offset, 2, 30);
    array_set(my_arena, my_array_offset, 3, 40);
    array_set(my_arena, my_array_offset, 4, 50);
    
    array_print(my_arena, my_array_offset, arr_len);
    arena_dump(my_arena);

    printf("\n---Try On Linked List Berbasis Offset---\n");
    LinkedList my_list;
    ll_init(&my_list);

    //input 3 data linkedlist
    ll_insert_last(my_arena, &my_list, 100);
    ll_insert_last(my_arena, &my_list, 200);
    ll_insert_last(my_arena, &my_list, 300);

    //tampil isi linkedlist
    ll_print(my_arena, &my_list);
    arena_dump(my_arena);

    //clear
    arena_destroy(my_arena);
    return 0;
}