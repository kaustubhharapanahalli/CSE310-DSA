/*
 * Copyright (C) 2022 Kaustubh Manoj Harapanahalli
 */

#ifndef UTIL_HPP_
#define UTIL_HPP_

#include <iostream>
#include <string>

#include "util.hpp"  // NOLINT

typedef struct ELEMENT_TAG {
  int key;
  int value;
  int index;
} ELEMENT;

typedef struct HEAP_TAG {
  int capacity, element_count;
  ELEMENT *A;
  int heap_size;
} HEAP;

void readFile(HEAP *heapObject);

class PriorityQueue {
 public:
  int Parent(int size);
  int Left(int size);
  int Right(int size);
  void Swap(ELEMENT *array, int index, int largest);
};

#endif  // UTIL_HPP_
