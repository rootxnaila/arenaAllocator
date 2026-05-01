#include <stdio.h>
#include "array.h"

//bikin array: booking memori sebesar length * sizeof(int)
size_t array_create(Arena* arena, size_t length) {
    return arena_alloc(arena, length * sizeof(int));
}

//ngisi nilai ke index tertentu
void array_set(Arena* arena, size_t array_offset, size_t index, int value) {
    //offset array jd pointer (array of integer)
    int* arr = (int*)arena_get(arena, array_offset);
    if (arr) {
        arr[index] = value;
    }
}

void array_print(Arena* arena, size_t array_offset, size_t length) {
    int* arr = (int*)arena_get(arena, array_offset);
    if (!arr) return;

    printf("Isi Array (offset mulai: %zu): [", array_offset);
    for (size_t i = 0; i < length; i++) {
        printf("%d", arr[i]);
        if (i < length - 1) printf(", ");
    }
    printf("]\n");
}