#include <stdio.h>
#include "arena.h"

int main() {
    printf("DEMO ARENA ALLOCATOR (progress week 1) ===\n");
    //book arena
    Arena* my_arena = arena_create(20);
    
    printf("\n[Tahap 1] kondisi arena awal:");
    arena_dump(my_arena);

    //simulasi alokasi  
    printf("[Tahap 2] alokasi untuk 2 buah integer (total 8 byte)...");
    size_t offset_data1 = arena_alloc(my_arena, sizeof(int));
    size_t offset_data2 = arena_alloc(my_arena, sizeof(int));
    
    int* ptr1 = (int*)arena_get(my_arena, offset_data1);
    int* ptr2 = (int*)arena_get(my_arena, offset_data2);
    if(ptr1) *ptr1 = 15;
    if(ptr2) *ptr2 = 30;

    arena_dump(my_arena);

    //reset arena
    printf("[Tahap 3] reset arena...");
    arena_reset(my_arena);
    arena_dump(my_arena);

    arena_destroy(my_arena);
    return 0;
}