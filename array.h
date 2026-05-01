#ifndef ARRAY_H
#define ARRAY_H

#include "arena.h"

size_t array_create(Arena* arena, size_t length);
void array_set(Arena* arena, size_t array_offset, size_t index, int value);
void array_print(Arena* arena, size_t array_offset, size_t length);

#endif