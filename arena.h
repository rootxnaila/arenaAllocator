#ifndef ARENA_H
#define ARENA_H

#include <stddef.h>

typedef struct {
    unsigned char* buffer; //pointer ke memori asli gudang
    size_t capacity;       
    size_t offset; //jarak
} Arena;

//main function adt
Arena* arena_create(size_t capacity);
size_t arena_alloc(Arena* arena, size_t size);
void* arena_get(Arena* arena, size_t offset);
void arena_reset(Arena* arena);
void arena_dump(Arena* arena);

// clear arena di akhir program
void arena_destroy(Arena* arena);

#endif