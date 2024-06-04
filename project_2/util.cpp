/*
 * Copyright (C) 2022 Kaustubh Manoj Harapanahalli
 */

#include "util.hpp"  // NOLINT

#include <iostream>

int PriorityQueue::Parent(int index) {
  int parent = index / 2;
  return parent;
}

int PriorityQueue::Left(int index) {
  int left = 2 * index;
  return left;
}

int PriorityQueue::Right(int index) {
  int right = (2 * index) + 1;
  return right;
}

void PriorityQueue::Swap(ELEMENT *array, int index_1, int index_2) {
  int value, index;
  value = array[index_1].value;
  index = array[index_1].key;
  array[index_1].value = array[index_2].value;
  array[index_1].key = array[index_2].key;
  array[index_2].value = value;
  array[index_2].key = index;
}

void readFile(HEAP *heapObject) {
  int size;
  FILE *fp;

  fp = fopen("HEAPifile.txt", "r");
  if (fp == NULL) {
    std::cout << "Error: cannot open file HEAPifile.txt" << std::endl;
    exit(1);
  }

  fscanf(fp, "%d", &size);

  ELEMENT inputArray[size];  // NOLINT

  if (size == 0) {
    std::cout << "Error: cannot allocate memory" << std::endl;
    exit(1);
  }

  for (int i = 1; i <= size; i++) {
    inputArray[i].key = i;
    fscanf(fp, "%d", &inputArray[i].value);
  }
  fclose(fp);
  heapObject->element_count = size;
  heapObject->A = inputArray;
  heapObject->heap_size = size;

  for (int i = 1; i <= heapObject->heap_size; i++) {
    std::cout << heapObject->A[i].key << " :: " << heapObject->A[i].value
              << std::endl;
  }
}
