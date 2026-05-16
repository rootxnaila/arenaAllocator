#ifndef ARRAY_H
#define ARRAY_H

#include "arena.h"

size_t array_create(Arena* arena, size_t length); // meminta alokasi ruang memori di arena sesuai panjang array yang ditentukan
void array_set(Arena* arena, size_t array_offset, size_t index, int value); // memasukkan nilai integer ke indeks tertentu dengan menerjemahkan offset menjadi pointer
void array_print(Arena* arena, size_t array_offset, size_t length); // cetak seluruh isi array berdasarkan panjang dan offset yang diberikan

#endif