#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "arena.h"
#include "queue.h"

#define ARENA_CAPACITY (20 * 1024 * 1024) //kapasitas diperbesar buat dataset 10.000

int main() {
    printf("=== EKSPERIMEN BATCH PROCESSING: AI DATA PIPELINE ===\n\n");
    
    Arena* pipeline_arena = arena_create(ARENA_CAPACITY);
    Queue ai_queue;
    queue_init(&ai_queue);

    clock_t start_time = clock();

    printf("1. Membaca file dataset dan memasukkan ke Queue (Enqueue)...\n");
    
    FILE *file = fopen("dataset_10k.txt", "r");
    if (!file) {
        printf("Error: File dataset_10k.txt tidak ditemukan di folder ini!\n");
        arena_destroy(pipeline_arena);
        return 1;
    }

    char line[128];
    int enqueue_count = 0;
    
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0; 
        
        if (!enqueue(pipeline_arena, &ai_queue, line)) {
            printf("CRITICAL ERROR: Arena Penuh di baris ke-%d!\n", enqueue_count);
            break;
        }
        enqueue_count++;
    }
    fclose(file);
    printf(" -> Success Enqueue %d data!\n\n", enqueue_count);

    printf("2. Mulai Pemrosesan Data secara massal (Dequeue)...\n");
    char processed_message[128];
    int dequeue_count = 0;
    while (!is_empty(&ai_queue)) {
        if (dequeue(pipeline_arena, &ai_queue, processed_message)) {
            dequeue_count++;
        }
    }
    printf(" -> Success memproses %d data!\n", dequeue_count);

    printf("\n3. Batch Done. Delete Memory Instantly O(1)...\n");
    arena_reset(pipeline_arena);
    
    clock_t end_time = clock();
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("\n[Last Status Arena] Offset = %zu (All Clear!)\n", pipeline_arena->offset);
    printf("Execute Time Total: %f detik\n", time_taken);

    arena_destroy(pipeline_arena);
    return 0;
}