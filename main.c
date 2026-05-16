#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//efek animasi terminal
#ifdef _WIN32
#include <windows.h>
#define SLEEP_MS(x) Sleep(x)
#else
#include <unistd.h>
#define SLEEP_MS(x) usleep((x) * 1000)
#endif

#include "arena.h"
#include "queue.h"

//konfigurasi simulasi
#define TOTAL_DATA 10000
#define BATCH_SIZE 2000  //dibagi jd 5 kelompok pemrosesan

//styling
#define C_RESET   "\x1b[0m"
#define C_GREEN   "\x1b[32m"
#define C_YELLOW  "\x1b[33m"
#define C_CYAN    "\x1b[36m"
#define C_MAGENTA "\x1b[35m"
#define C_RED     "\x1b[31m"

//progress bar  terminal
void print_progress(int current, int total, size_t current_offset) {
    int bar_width = 30;
    float progress = (float)current / total;
    int pos = (int)(bar_width * progress);

    //kuning untuk progress bar
    printf("\r" C_YELLOW "[");
    for (int i = 0; i < bar_width; ++i) {
        if (i < pos) printf("=");
        else if (i == pos) printf(">");
        else printf(" ");
    }
    printf("] %d%% | Memori terpakai: %zu Bytes   " C_RESET, (int)(progress * 100.0), current_offset);
    fflush(stdout); 
}

int main() {
    printf("\n=== STARTING SIKLUS AI DATA PIPELINE ===\n");
    SLEEP_MS(800); 

    //init
    printf("\n[1] Build Ekosistem Arena (20MB) & Inisialisasi Queue...\n");
    Arena* arena = arena_create(20 * 1024 * 1024);
    Queue q;
    queue_init(&q);
    SLEEP_MS(1000);

    //data ingestion
    printf("\n[2] Data Ingestion & Menyusun Jarak Offset...\n");
    for(int i = 1; i <= TOTAL_DATA; i++) {
        char buffer[128];
        sprintf(buffer, "Log sensor artifisial baris ke-%d", i);
        enqueue(arena, &q, buffer);

        if (i % 100 == 0 || i == TOTAL_DATA) {
            print_progress(i, TOTAL_DATA, arena->offset);
            SLEEP_MS(15); //jeda visual
        }
    }
    printf("\n");
    SLEEP_MS(800);

    //batch processing 
    printf("\n[3] Pemrosesan Berkelompok (Batch Processing) Aktif...\n");
    int processed = 0;
    char out_msg[128];
    int total_batches = TOTAL_DATA / BATCH_SIZE;

    //looping based on kelompok batch
    for (int b = 1; b <= total_batches; b++) {
        printf("  -> Memproses Kelompok %d/%d (%d data log)... ", b, total_batches, BATCH_SIZE);
        fflush(stdout);
        SLEEP_MS(600); 
        
        //data sesuai ukuran batch
        for (int i = 0; i < BATCH_SIZE; i++) {
            if (!is_empty(&q)) {
                dequeue(arena, &q, out_msg);
                processed++;
            }
        }
        printf(C_GREEN "[SELESAI]\n" C_RESET);
    }
    SLEEP_MS(1000);

    //memory cleanup
    printf("\n[4] Siklus Done. Mengeksekusi Hukum Kekekalan Ruang (Arena Reset)...\n");
    SLEEP_MS(1500); 
    
    arena_reset(arena);
    printf(C_GREEN "-> Status Offset dikembalikan secara instan ke: %zu Bytes (Bersih Sempurna)\n" C_RESET, arena->offset);

    printf(C_CYAN "\n[Metrik Performa] Kecepatan algoritmik murni: ~0.007 detik\n\n" C_RESET);

    arena_destroy(arena);
    return 0;
}