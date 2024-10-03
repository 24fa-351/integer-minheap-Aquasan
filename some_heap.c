
#include "some_heap.h"

#include <stdio.h>
#include <stdlib.h>

#define KEY_NOT_PRESENT -1

heap_t *heap_create(int capacity) {
    heap_t *heap = (heap_t *)malloc(sizeof(heap_t));
    heap->data = (heap_node_t *)malloc(sizeof(heap_node_t) * capacity);
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void heap_free(heap_t *heap) {}

unsigned int heap_size(heap_t *heap) { return heap->size; }

unsigned int heap_parent(unsigned int index) {
    if (index == 0) return 0;  
    return (index - 1) / 2;    // Return the index of the parent
}

unsigned int heap_left_child(unsigned int index) {
    return (2 * index + 1);  // Return the index of the left child
}

unsigned int heap_right_child(unsigned int index) {
    return (2 * index + 2);  // Return the index of the right child
}

unsigned int heap_level(unsigned int index) {
    unsigned int level = 0;
    while (index > 0) {
        index = (index - 1) / 2;  // Move to the parent
        level++;
    }
    return level;
}

void heap_print(heap_t *heap, FILE *file) {
    for (int ix = 0; ix < heap_size(heap); ix++) {
        fprintf(file, "%3d - %3d : " HEAP_KEY_FORMAT "\n", heap_level(ix), ix,
                heap->data[ix].key);
    }
    fprintf(file, "\n");
}

void heap_swap(heap_t *heap, int index1, int index2) {}

void heap_bubble_up(heap_t *heap, int index) {}

void heap_bubble_down(heap_t *heap, int index) {}

void heap_insert(heap_t *heap, heap_key_t key, heap_value_t data) {
    if (heap_size(heap) == heap->capacity) {
        return;
    }

    heap->data[heap_size(heap)].key = key;
    heap->data[heap_size(heap)].value = data;
    heap->size++;

    heap_bubble_up(heap, heap_size(heap) - 1);
}

heap_key_t heap_remove_min(heap_t *heap) {
    if (heap_size(heap) == 0) {
        return (heap_key_t)-1; 
    }

    heap_key_t min_key = heap->data[0].key;  

    heap->size--;  

    // Move the last element to the root
    heap->data[0] = heap->data[heap_size(heap)];

    // Bubble down to maintain heap property
    heap_bubble_down(heap, 0);

    return min_key;  
}
