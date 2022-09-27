/*
 * Copyright (C) 2022 Kaustubh Manoj Harapanahalli
 */

#include <stdio.h>
#include <stdlib.h>

#include <cstring>
#include <iostream>

#include "insertion_sort.hpp"  // NOLINT
#include "merge_sort.hpp"      // NOLINT
#include "quick_sort.hpp"      // NOLINT

int main(int argc, char *argv[]) {
  FILE *fp;
  int alg, flag, i, n, count_EWC;
  int *A;
  int print_result, print_array_at_each_step;

  if (argc < 3) {
    std::cout << "Usage: ./PJ1 alg flag" << std::endl;
    std::cout << "       alg should be in {InsertionSort, MergeSort, QuickSort}"
              << std::endl;
    std::cout << "       flag should be in {0, 1}" << std::endl;
    exit(1);
  }

  if (strcmp(argv[1], "InsertionSort") && strcmp(argv[1], "MergeSort") &&
      strcmp(argv[1], "QuickSort")) {
    // std::cout << "Error: " << argv[1]
    //           << " is NOT in {InsertionSort, MergeSort, QuickSort}"
    //           << std::endl;
    std::cout << "Usage: ./PJ1 alg flag" << std::endl;
    std::cout << "       alg should be in {InsertionSort, MergeSort, QuickSort}"
              << std::endl;
    std::cout << "       flag should be in {0, 1}" << std::endl;
    exit(1);
  }

  flag = atoi(argv[2]);

  if (flag != 0 && flag != 1) {
    std::cout << "Usage: ./PJ1 alg flag" << std::endl;
    std::cout << "       alg should be in {InsertionSort, MergeSort, QuickSort}"
              << std::endl;
    std::cout << "       flag should be in {0, 1}" << std::endl;
    exit(1);
  }

  if (strcmp(argv[1], "InsertionSort") == 0) {
    alg = 1;
  } else if (strcmp(argv[1], "MergeSort") == 0) {
    alg = 2;
  } else if (strcmp(argv[1], "QuickSort") == 0) {
    alg = 3;
  }

  fp = fopen("INPUT.txt", "r");
  if (fp == NULL) {
    std::cout << "Error: cannot open file INPUT.txt" << std::endl;
    exit(1);
  }

  fscanf(fp, "%d", &print_result);
  fscanf(fp, "%d", &print_array_at_each_step);

  fscanf(fp, "%d", &n);
  A = reinterpret_cast<int *>(malloc(n * sizeof(int)));

  if (A == NULL) {
    std::cout << "Error: cannot allocate memory" << std::endl;
    exit(1);
  }

  for (i = 0; i < n; i++) {
    fscanf(fp, "%d", &A[i]);
  }

  fclose(fp);

  switch (alg) {
    case 1:
      count_EWC = InsertionSort(A, n, flag, print_array_at_each_step);
      break;

    case 2:
      count_EWC = MergeSort(A, 0, n - 1, flag, print_array_at_each_step);
      break;

    case 3:
      count_EWC = QuickSort(A, 0, n - 1, flag, print_array_at_each_step);
      break;

    default:
      break;
  }

  if (print_result) {
    std::cout << "A[1:" << n << "] after sorting: ";

    for (i = 0; i < n - 1; i++) {
      std::cout << A[i] << " ";
    }

    std::cout << A[n - 1] << std::endl;
  }

  std::cout << "Number of EWCs: " << count_EWC << std::endl;

  delete A;

  return 0;
}
