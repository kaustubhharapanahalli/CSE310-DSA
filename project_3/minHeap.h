// Copyright (c) 2022 - Kaustubh Harapanahalli

#ifndef MINHEAP_H_
#define MINHEAP_H_

#include <iostream>

#include "graph.h"  // NOLINT

struct heapNode {
  int value;
  float distance;
};

struct heap {
  int size;
  int capacity;
  int *position;
  struct heapNode **array;
};

class minHeapIm {
 public:
  minHeapIm();
  struct heapNode *newMinHeapNode(int value, float distance);
  struct heap *createMinHeap(int capacity);
  void swapMinHeapNode(struct heapNode **a, struct heapNode **b);
  void minHeapify(struct heap *minheap, int index);
  int isEmpty(struct heap *minheap);
  struct heapNode *extractMin(struct heap *minheap);
  void decreaseKey(struct heap *minheap, int value, float distance);
  bool isInMinHeap(struct heap *minheap, int value);
};

#endif  // MINHEAP_H_
