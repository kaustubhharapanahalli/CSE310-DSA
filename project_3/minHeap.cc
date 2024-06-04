// Copyright (c) 2022 - Kaustubh Harapanahalli

#include "minHeap.h"

#include <iostream>

minHeapIm::minHeapIm() {}

struct heapNode *minHeapIm::newMinHeapNode(int value, float distance) {
  struct heapNode *minHeapNode =
      (struct heapNode *)malloc(sizeof(struct heapNode));
  minHeapNode->value = value;
  minHeapNode->distance = distance;

  return minHeapNode;
}

struct heap *minHeapIm::createMinHeap(int capacity) {
  struct heap *minHeap = (struct heap *)malloc(sizeof(struct heap));
  minHeap->position = reinterpret_cast<int *>(malloc(capacity * sizeof(int)));
  minHeap->size = 0;
  minHeap->capacity = capacity;
  minHeap->array =
      (struct heapNode **)malloc(capacity * sizeof(struct heapNode *));

  return minHeap;
}

void minHeapIm::swapMinHeapNode(struct heapNode **a, struct heapNode **b) {
  struct heapNode *temp = *a;
  *a = *b;
  *b = temp;
}

void minHeapIm::minHeapify(struct heap *minheap, int index) {
  int smallest, left, right;
  smallest = index;
  left = 2 * index + 1;
  right = 2 * index + 2;

  if (left < minheap->size &&
      minheap->array[left]->distance < minheap->array[smallest]->distance) {
    smallest = left;
  }

  if (right < minheap->size &&
      minheap->array[right]->distance < minheap->array[smallest]->distance) {
    smallest = right;
  }

  if (smallest != index) {
    heapNode *smallestNode = minheap->array[smallest];
    heapNode *indexNode = minheap->array[index];

    minheap->position[smallestNode->value] = index;
    minheap->position[indexNode->value] = smallest;

    swapMinHeapNode(&minheap->array[smallest], &minheap->array[index]);

    minHeapify(minheap, smallest);
  }
}

int minHeapIm::isEmpty(struct heap *minheap) { return minheap->size == 0; }

struct heapNode *minHeapIm::extractMin(struct heap *minheap) {
  if (isEmpty(minheap)) {
    return NULL;
  }

  struct heapNode *root_node = minheap->array[0];
  struct heapNode *last_node = minheap->array[minheap->size - 1];
  minheap->array[0] = last_node;

  minheap->position[root_node->value] = minheap->size - 1;
  minheap->position[last_node->value] = 0;

  --minheap->size;
  minHeapify(minheap, 0);

  return root_node;
}

void minHeapIm::decreaseKey(struct heap *minheap, int value, float distance) {
  int i = minheap->position[value];
  // std::cout << "I val: " << i << " - Distance: " << distance << std::endl;

  minheap->array[i]->distance = distance;
  // std::cout << "P dist: " << minheap->array[(i - 1) / 2]->distance <<
  // std::endl;
  while (i &&
         minheap->array[i]->distance < minheap->array[(i - 1) / 2]->distance) {
    // std::cout << "Swapping" << std::endl;
    minheap->position[minheap->array[i]->value] = (i - 1) / 2;
    minheap->position[minheap->array[(i - 1) / 2]->value] = i;
    swapMinHeapNode(&minheap->array[i], &minheap->array[(i - 1) / 2]);

    i = (i - 1) / 2;
  }
}

bool minHeapIm::isInMinHeap(struct heap *minheap, int value) {
  if (minheap->position[value] < minheap->size) {
    return true;
  }

  return false;
}

/*****************************************************
 *****************************************************
 * Min heap implementation for the initial version.
 *****************************************************
 *****************************************************/

// int MinHeap::Parent(int index) {
//   int parent = index / 2;
//   return parent;
// }

// int MinHeap::Left(int index) {
//   int left = 2 * index;
//   return left;
// }

// int MinHeap::Right(int index) {
//   int right = (2 * index) + 1;
//   return right;
// }

// void MinHeap::Swap(struct element *array, int index_i, int index_j) {
//   int value, index;
//   value = array[index_i].value;
//   index = array[index_i].key;
//   array[index_i].value = array[index_j].value;
//   array[index_i].key = array[index_j].key;
//   array[index_j].value = value;
//   array[index_j].key = index;
// }

// void MinHeap::MinHeapify(struct element *array, int index) {
//   int left_index = Left(index);
//   int right_index = Left(index);

//   int swap_with;

//   if ((left_index <= this->array->heap_size) &&
//       array[left_index].value < array[index].value) {
//     swap_with = left_index;
//   } else {
//     swap_with = index;
//   }

//   if ((right_index <= this->array->heap_size) &&
//       (array[right_index].value < array[swap_with].value)) {
//     swap_with = right_index;
//   }

//   if (swap_with != index) {
//     Swap(array, index, swap_with);
//     MinHeapify(array, swap_with);
//   }
// }

// int MinHeap::Minimum() {
//   if (this->array->heap_size < 1) {
//     fprintf(stderr, "Heap underflow");
//   }
//   return this->array->A[1].value;
// }

// returnValue MinHeap::ExtractMin() {
//   int key = this->array->A[1].key;
//   int min = Minimum();
//   this->array->A[1].value = this->array->A[this->array->heap_size].value;
//   this->array->A[1].key = this->array->A[this->array->heap_size].key;
//   this->array->heap_size = this->array->heap_size - 1;
//   MinHeapify((this->array)->A, 1);

//   returnValue result = {min, key};

//   return result;
// }

// void MinHeap::Insert(int value) {
//   if (value == this->array->A[this->array->heap_size].value) {
//     fprintf(stderr, "heap overflow");
//     return;
//   }

//   this->array->heap_size++;

//   this->array->element_count++;
//   this->array->A[this->array->heap_size].key = this->array->element_count;
//   this->array->A[this->array->heap_size].value = value;

//   MinHeapify((this->array)->A, this->array->heap_size);
// }

// void MinHeap::DecreaseKey(int index, int value) {
//   if (index > this->array->heap_size) {
//     fprintf(stderr, "Error: Invalid position or newKey in DecreaseKey\n");
//     return;
//   }

//   if (this->array->A[index].value <= value) {
//     fprintf(stderr, "Error: Invalid position or newKey in DecreaseKey\n");
//     return;
//   }

//   this->array->A[index].value = value;
//   int i = this->array->A[index].index;

//   while ((i > 1) &&
//          (this->array->A[Parent(i)].value > this->array->A[i].value)) {
//     Swap((this->array)->A, Parent(i), i);
//     i = Parent(i);
//   }
// }
