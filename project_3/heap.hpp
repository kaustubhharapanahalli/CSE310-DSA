/*
 * Copyright (C) 2022 Kaustubh Manoj Harapanahalli
 */

#ifndef HEAP_HPP_
#define HEAP_HPP_

#include <iostream>
#include <tuple>

#include "util.hpp"  // NOLINT

struct returnValue {
  int val1;
  int val2;
};

class MaxHeap {
 public:
  MaxHeap(HEAP *array) { this->array = array; };  // NOLINT
  void MaxHeapify(ELEMENT *array, int index);
  int Maximum();
  void BuildHeap();
  returnValue ExtractMax();
  void IncreaseKey(int index, int value);
  void Insert(int value);
  void DecreaseKey(int index, int value);
  int Delete(int value);

 private:
  PriorityQueue priority_queue;
  HEAP *array;
};

class MinHeap {
 public:
  MinHeap(HEAP *array) { this->array = array; };  // NOLINT
  void MinHeapify(ELEMENT *array, int index);
  int Minimum();
  void BuildHeap();
  returnValue ExtractMin();
  void IncreaseKey(int index, int value);
  void Insert(int value);
  void DecreaseKey(int index, int value);
  int Delete(int value);

 private:
  PriorityQueue priority_queue;
  HEAP *array;
};

// class DoubleHeap {
//  public:
//   HEAP *array;
//   void MaxHeapify();
//   void BuildHeap();
//   void ExtractMax();
//   void IncreaseKey();
//   void Insert();
//   void DecreaseKey();
//   void Delete();
// };

#endif  // HEAP_HPP_
