# Heap Management System

## Overview

The **Heap Management System** is a C-based simulation of memory allocation and deallocation using different strategies. It supports four allocation strategies: **First Fit**, **Best Fit**, **Worst Fit**, and **Buddy System**. The system simulates a heap and provides functionalities to allocate, free, and display memory blocks.

---

## Features

1. **Memory Allocation**:
   - Supports four allocation strategies:
     - **First Fit**: Allocates the first available block that is large enough.
     - **Best Fit**: Allocates the smallest available block that is large enough.
     - **Worst Fit**: Allocates the largest available block.
     - **Buddy System**: Allocates memory in powers of 2 and splits blocks as needed.

2. **Memory Deallocation**:
   - Frees allocated memory blocks by index.
   - Merges adjacent free blocks to reduce fragmentation.

3. **Memory Display**:
   - Displays the current state of the heap, showing allocated and free blocks.

4. **Simulated Heap**:
   - Uses a fixed-size simulated heap (`HEAP_SIZE = 1024`).

---

## How It Works

1. **Initialization**:
   - The heap is initialized as a single free block of size `HEAP_SIZE`.

2. **Allocation**:
   - Depending on the chosen strategy, the system searches for a suitable block to allocate.
   - If the block is larger than required, it is split into smaller blocks (except in the Buddy System, where blocks are split into powers of 2).

3. **Deallocation**:
   - When a block is freed, it is marked as free, and adjacent free blocks are merged to reduce fragmentation.

4. **Display**:
   - The system displays the current state of the heap, showing the size and status (allocated or free) of each block.

---

## Usage

### Compilation and Execution

#### On Windows, macOS, and Linux:
1. Open a terminal (Command Prompt on Windows, Terminal on macOS/Linux).
2. Navigate to the directory containing the `heap_management.c` file.
3. Compile the code using GCC:

   - **On Windows:**
     ```bash
     gcc heap_management.c -o heap_management.exe
     heap_management.exe
     ```

   - **On macOS/Linux:**
     ```bash
     gcc heap_management.c -o heap_management
     ./heap_management
     ```

---
