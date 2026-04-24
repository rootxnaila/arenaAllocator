#include "arena.h"
#include <stdio.h>
#include <stdlib.h>

//create arena
Arena* arena_create(size_t capacity) { 
    Arena* arena = (Arena*)malloc(sizeof(Arena));
    if (!arena) return NULL;
    
    arena->buffer = (unsigned char*)malloc(capacity);
    if (!arena->buffer) {
        free(arena);
        return NULL;
    }
    
    arena->capacity = capacity;
    arena->offset = 0; //mulai dr nol
    return arena;
}

// minta memori, balikin offset
size_t arena_alloc(Arena* arena, size_t size) {
    // cek ruang avail
    if (arena->offset + size > arena->capacity) {
        printf("Error: Kapasitas Arena Penuh!\n");
        return (size_t)-1; // gagal
    }
    
    size_t current_offset = arena->offset;
    arena->offset += size; 
    return current_offset;
}

//terjemah angka offset jd pointer asli saat data ingin dibaca/ditulis
void* arena_get(Arena* arena, size_t offset) {
    if (offset >= arena->capacity) return NULL;
    return (void*)(arena->buffer + offset);
}

//delete all instan
void arena_reset(Arena* arena) {
    arena->offset = 0; 
}

//visualisasi status arena di terminal
void arena_dump(Arena* arena) {
    printf("\n[status arena] terisi: %zu byte / kapasitas: %zu byte\n", arena->offset, arena->capacity);
    printf("memory layout:\n|");
    for (size_t i = 0; i < arena->capacity; i++) {
        if (i < arena->offset) {
            printf(" # |"); // '#' memori dipakai
        } else {
            printf(" . |"); // '.' memori kosong
        }
        
        // mecah baris setiap 10 kotak
        if ((i + 1) % 10 == 0 && i + 1 != arena->capacity) {
            printf("\n|");
        }
    }
    printf("\n\n");
}

void arena_destroy(Arena* arena) {
    if (arena) {
        free(arena->buffer);
        free(arena);
    }
}