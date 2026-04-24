# AI Data Pipeline Batcher

this project is an implementation of a custom memory allocator utilizing the Arena Allocator pattern. the system is designed to tackle memory fragmentation and the overhead of repeated malloc/free calls, specifically when processing massive data streams for AI pipelines.

this system was developed as the Final Project for the Data Structure course 2026 Universitas Negeri Malang by:
- Naila Rizki Amalya - core engineering & system architecture
- Nur Rahmawati - data analytics & experimentation
- Nathanael Purwanto - documentation & design

## Core Concept
inspired by the article ["Untangling Lifetimes: The Arena Allocator"](https://www.dgtlgrove.com/p/untangling-lifetimes-the-arena-allocator) by Ryan Fleury, this system does not free memory on a per-object basis. instead, memory is allocated in a single large block (arena) upfront. raw data is queued within this arena. once a data batch is processed, the entire arena memory is instantly reset with an O(1) time complexity.

## System Architecture & Rules
- Arena as ADT: memory access is strictly isolated. data structures cannot access the buffer directly and must route through the API (e.g., arena_alloc and arena_reset).
- Offset-Based Pointers: absolute C memory pointers are removed at the data structure level. node relationships in the Linked List and Queue are strictly represented as integers (offsets).
- Zero Malloc in Data Structures: no malloc, calloc, or free calls are made during enqueue or dequeue operations.
- ASCII Memory Dump: includes a built-in arena_dump() function to visualize the memory layout state as a 2D grid in the terminal for debugging purposes.

## Directory Structure
the code is written in standard C with a modular architecture:
- arena.h / arena.c : core allocator engine.
- linkedlist.h / linkedlist.c : offset-based linked node foundation.
- queue.h / queue.c : FIFO logic for data processing.
- main.c : program entry point and simulation scenarios.

## How to Run
ensure the GCC compiler is installed in your environment. open a terminal in the project directory and execute the following commands:

```bash
# Compile all files simultaneously
gcc main.c arena.c -o program_arena

# Execute the program
./program_arena
