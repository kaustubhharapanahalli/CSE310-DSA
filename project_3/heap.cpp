/*
 * Copyright (C) 2022 Kaustubh Manoj Harapanahalli
 */

#include "heap.hpp"  //NOLINT

#include <iostream>
#include <limits>

#include "util.hpp"  //NOLINT

/**************************************************
 *
 * Implementation of functions for MaxHeap
 *
 **************************************************/

void MaxHeap::MaxHeapify(ELEMENT* array, int index) {
  int left = priority_queue.Left(index);
  int right = priority_queue.Right(index);
  int largest;
  if ((left <= this->array->heap_size) &&
      (array[left].value > array[index].value)) {
    largest = left;
  } else {
    largest = index;
  }

  if ((right <= this->array->heap_size) &&
      (array[right].value > array[largest].value)) {
    largest = right;
  }

  if (largest != index) {
    priority_queue.Swap(array, index, largest);
    MaxHeapify(array, largest);
  }
}

void MaxHeap::BuildHeap() {
  int n = this->array->heap_size;
  for (int i = (n / 2); i > 0; i--) {
    MaxHeapify((this->array)->A, i);
  }
}

int MaxHeap::Maximum() {
  if (this->array->heap_size < 1) {
    fprintf(stderr, "Heap underflow");
  }
  return this->array->A[1].value;
}

returnValue MaxHeap::ExtractMax() {
  int key = this->array->A[1].key;
  int max = Maximum();
  this->array->A[1].value = this->array->A[this->array->heap_size].value;
  this->array->A[1].key = this->array->A[this->array->heap_size].key;

  this->array->heap_size = this->array->heap_size - 1;
  MaxHeapify((this->array)->A, 1);

  returnValue result = {max, key};

  return result;
}

void MaxHeap::IncreaseKey(int index, int value) {
  if (index > this->array->heap_size) {
    fprintf(stderr, "Error: Invalid position or newKey in IncreaseKey\n");
    return;
  }

  if (this->array->A[index].value >= value) {
    fprintf(stderr, "Error: Invalid position or newKey in IncreaseKey\n");
    return;
  }

  this->array->A[index].value = value;
  int i = this->array->A[index].key;

  while ((i > 1) && (this->array->A[priority_queue.Parent(i)].value <
                     this->array->A[i].value)) {
    priority_queue.Swap((this->array)->A, priority_queue.Parent(i), i);
    i = priority_queue.Parent(i);
  }
}

void MaxHeap::Insert(int value) {
  if (this->array->heap_size >= this->array->capacity) {
    fprintf(stderr, "Error: Insertion to a null/full heap\n");
    return;
  }

  this->array->heap_size++;

  // this->array->A[this->array->heap_size].key = this->array->heap_size;
  this->array->element_count++;
  this->array->A[this->array->heap_size].key = this->array->element_count;
  this->array->A[this->array->heap_size].value =
      std::numeric_limits<int>::min();

  IncreaseKey(this->array->heap_size, value);
}

void MaxHeap::DecreaseKey(int index, int value) {
  if (index > this->array->heap_size) {
    fprintf(stderr, "Error: Invalid position or newKey in DecreaseKey\n");
  }

  if (this->array->A[index].value < value) {
    fprintf(stderr, "Error: Invalid position or newKey in DecreaseKey\n");
    return;
  }

  this->array->A[index].value = value;
  int i = this->array->A[index].index;

  MaxHeapify((this->array)->A, i);
}

int MaxHeap::Delete(int index) {
  if (index > this->array->heap_size) {
    fprintf(stderr, "heap overflow");
    return 0;
  }

  int element = this->array->A[index].value;
  this->array->A[index].value = this->array->A[this->array->heap_size].value;
  this->array->heap_size--;

  if (index > 1 && index <= this->array->heap_size &&
      this->array->A[index].value > this->array->A[index / 2].value) {
    while (index > 1 &&
           this->array->A[index].value > this->array->A[index / 2].value) {
      priority_queue.Swap((this->array)->A, index, index / 2);
      index = index / 2;
    }
  } else {
    MaxHeapify((this->array)->A, index);
  }

  return element;
}

/**************************************************
 *
 * Implementation of functions for MinHeap
 *
 **************************************************/

void MinHeap::MinHeapify(ELEMENT* array, int index) {
  int left = priority_queue.Left(index);
  int right = priority_queue.Right(index);
  int smallest;
  if ((left <= this->array->heap_size) &&
      (array[left].value < array[index].value)) {
    smallest = left;
  } else {
    smallest = index;
  }

  if ((right <= this->array->heap_size) &&
      (array[right].value < array[smallest].value)) {
    smallest = right;
  }

  if (smallest != index) {
    priority_queue.Swap(array, index, smallest);
    MinHeapify(array, smallest);
  }
}

void MinHeap::BuildHeap() {
  int n = this->array->heap_size;
  for (int i = (n / 2); i > 0; i--) {
    MinHeapify((this->array)->A, i);
  }
}

int MinHeap::Minimum() {
  if (this->array->heap_size < 1) {
    fprintf(stderr, "Heap underflow");
  }
  return this->array->A[1].value;
}

returnValue MinHeap::ExtractMin() {
  int key = this->array->A[1].key;
  int min = Minimum();
  this->array->A[1].value = this->array->A[this->array->heap_size].value;
  this->array->A[1].key = this->array->A[this->array->heap_size].key;
  this->array->heap_size = this->array->heap_size - 1;
  MinHeapify((this->array)->A, 1);

  returnValue result = {min, key};

  return result;
}

void MinHeap::IncreaseKey(int index, int value) {
  if (index > this->array->heap_size) {
    fprintf(stderr, "Error: Invalid position or newKey in IncreaseKey\n");
    return;
  }

  if (this->array->A[index].value > value) {
    fprintf(stderr, "Error: Invalid position or newKey in IncreaseKey\n");
    return;
  }

  this->array->A[index].value = value;
  int i = this->array->A[index].key;
  MinHeapify((this->array)->A, i);
}

void MinHeap::Insert(int value) {
  if (value == this->array->A[this->array->heap_size].value) {
    fprintf(stderr, "heap overflow");
    return;
  }

  this->array->heap_size++;

  this->array->element_count++;
  this->array->A[this->array->heap_size].key = this->array->element_count;
  this->array->A[this->array->heap_size].value = value;

  MinHeapify((this->array)->A, this->array->heap_size);
}

void MinHeap::DecreaseKey(int index, int value) {
  if (index > this->array->heap_size) {
    fprintf(stderr, "Error: Invalid position or newKey in DecreaseKey\n");
    return;
  }

  if (this->array->A[index].value <= value) {
    fprintf(stderr, "Error: Invalid position or newKey in DecreaseKey\n");
    return;
  }

  this->array->A[index].value = value;
  int i = this->array->A[index].index;

  while ((i > 1) && (this->array->A[priority_queue.Parent(i)].value >
                     this->array->A[i].value)) {
    priority_queue.Swap((this->array)->A, priority_queue.Parent(i), i);
    i = priority_queue.Parent(i);
  }
}

int MinHeap::Delete(int index) {
  if (index > this->array->heap_size) {
    fprintf(stderr, "heap overflow");
    return 0;
  }

  int element = this->array->A[index].value;
  this->array->A[index].value = this->array->A[this->array->heap_size].value;
  this->array->heap_size--;

  if (index > 1 && index <= this->array->heap_size &&
      this->array->A[index].value < this->array->A[index / 2].value) {
    while (index > 1 &&
           this->array->A[index].value < this->array->A[index / 2].value) {
      priority_queue.Swap((this->array)->A, index, index / 2);
      index = index / 2;
    }
  } else {
    MinHeapify((this->array)->A, index);
  }

  return element;
}

// int DoubleHeap() {}
