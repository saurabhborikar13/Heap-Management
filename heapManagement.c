#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define HEAP_SIZE 1024  

typedef struct Block {
    int  size;       
    int free;          
    struct Block *next; 
} Block;

Block *free_list = NULL;  // Head of the free list
char heap[HEAP_SIZE];     // Simulated heap

// Initialize
void initialize() {
    free_list = (Block*) heap;
    free_list->size = HEAP_SIZE;
    free_list->free = 1;
    free_list->next = NULL;
}

// Merge
void merge() {
    Block *curr = free_list;
    while (curr && curr->next) {
        if (curr->free && curr->next->free) {
            curr->size += curr->next->size;
            curr->next = curr->next->next;
        } else {
            curr = curr->next;
        }
    }
}

// Get the next power of 2 for buddy system allocation
int  next_power_of_2(int  size) {
    int  power = 1;
    while (power < size) power *= 2;
    return power;
}

// Split a block 
void split(Block *block, int  size) {
    while (block->size / 2 >= size) {
        int  new_size = block->size / 2;
        Block *buddy = (Block*)((char*)block + new_size);
        buddy->size = new_size;
        buddy->free = 1;
        buddy->next = block->next;
        block->size = new_size;
        block->next = buddy;
    }
}

void *allocate(int  size, int type) {
    Block *curr = free_list, *selected = NULL;
    
    if (type == 4) {  // Buddy System
        size = next_power_of_2(size);
        while (curr) {
            if (curr->free && curr->size >= size) {
                split(curr, size);
                curr->free = 0;
                return (char*)curr;
            }
            curr = curr->next;
        }
        return NULL;
    }

    while (curr) {
        if (curr->free && curr->size >= size) {
            if (!selected || (type == 2 && curr->size < selected->size) || (type == 3 && curr->size > selected->size)) {
                selected = curr;
            }
        }
        curr = curr->next;
    }

    if (!selected) return NULL;

    if (selected->size > size) {
        Block *new_block = (Block*)((char*)selected + size);
        new_block->size = selected->size - size;
        new_block->free = 1;
        new_block->next = selected->next;
        selected->size = size;
        selected->next = new_block;
    }

    selected->free = 0;
    return (char*)selected;
}

// Free memory and merge adjacent free blocks
void free_mem(int index) {
    Block *curr = free_list;
    int i = 0;
    
    while (curr) {
        if (!curr->free) {  
            if (i == index) {  
                curr->free = 1;
                printf("Block %d of size %zu freed.\n", index, curr->size);
                merge();  
                return;
            }
            i++;  
        }
        curr = curr->next;
    }
    printf("Invalid index! No such allocated block.\n");
}

void display() {
    Block *curr = free_list;
    int i = 0;

    printf("\n============================================\n");
    printf("| %-10s | %-10s | %-10s |\n", "Index", "Size", "Status");
    printf("============================================\n");
    while (curr) {
        if (curr->free) {
            printf("| %-10s | %-10zu | %-10s |\n", "Free", curr->size, "Free");
        } else {
            printf("| %-10d | %-10zu | %-10s |\n", i, curr->size, "Allocated");
            i++;
        }
        curr = curr->next;
    }
    printf("============================================\n");
}

int main() {
    int allocation_type, choice, size, index;
    void *p = NULL;

    initialize();

    printf("\n-------------------------------------\n");
    printf("         HEAP MANAGEMENT SYSTEM     \n");
    printf("\n-------------------------------------\n");
    printf("Choose Allocation Strategy:\n");
    printf("1. First Fit\n");
    printf("2. Best Fit\n");
    printf("3. Worst Fit\n");
    printf("4. Buddy System\n");
    printf("Enter your choice: ");
    scanf("%d", &allocation_type);

    if (allocation_type < 1 || allocation_type > 4) {
        printf("Invalid selection! Exiting...\n");
        return 0;
    }

    while (1) {
        printf("\n----------------------------------\n");
        printf("1. Allocate Memory\n");
        printf("2. Free Memory (by index)\n");
        printf("3. Display Memory\n");
        printf("4. Exit\n");
        printf("----------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter size to allocate: ");
                scanf("%d", &size);
                p = allocate(size, allocation_type);
                if (p) {
                    printf("Allocated %d bytes using chosen strategy.\n", size);
                } else {
                    printf("Allocation failed. Not enough memory.\n");
                }
                break;
            case 2:
                printf("Enter index to free: ");
                scanf("%d", &index);
                free_mem(index);
                break;
            case 3:
                display();
                break;
            case 4:
                printf("Exiting program...\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}