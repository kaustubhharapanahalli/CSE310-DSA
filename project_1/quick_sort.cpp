/*
 * Copyright (C) 2022 Kaustubh Manoj Harapanahalli
 */
#include "quick_sort.hpp"  // NOLINT

#include <iostream>

int count_EWC_quick = 0;

int Partition(int list_of_numbers[], int init_index, int final_index, int flag,
              int print_array_at_each_step) {
  int final_element = list_of_numbers[final_index];
  int start = init_index - 1;

  for (int i = init_index; i <= final_index - 1; i++) {
    if (list_of_numbers[i] < final_element) {
      if (flag) {
        std::cout << "EWC: " << list_of_numbers[i] << " <= " << final_element
                  << "?" << std::endl;
      }
      start++;
      int temp = list_of_numbers[start];

      list_of_numbers[start] = list_of_numbers[i];

      if (print_array_at_each_step) {
        std::cout << "A[" << init_index + 1 << ":" << final_index + 1 << "]: ";
        for (int i = init_index; i < final_index + 1; i++) {
          std::cout << list_of_numbers[i] << " ";
        }

        std::cout << std::endl;
      }

      list_of_numbers[i] = temp;

      if (print_array_at_each_step) {
        std::cout << "A[" << init_index + 1 << ":" << final_index + 1 << "]: ";
        for (int i = init_index; i < final_index + 1; i++) {
          std::cout << list_of_numbers[i] << " ";
        }

        std::cout << std::endl;
      }
      count_EWC_quick++;

    } else {
      if (flag) {
        std::cout << "EWC: " << list_of_numbers[i] << " <= " << final_element
                  << "?" << std::endl;
      }
      count_EWC_quick++;
    }
  }

  int temp = list_of_numbers[start + 1];
  list_of_numbers[start + 1] = list_of_numbers[final_index];

  if (print_array_at_each_step) {
    std::cout << "A[" << init_index + 1 << ":" << final_index + 1 << "]: ";
    for (int i = init_index; i < final_index + 1; i++) {
      std::cout << list_of_numbers[i] << " ";
    }

    std::cout << std::endl;
  }

  list_of_numbers[final_index] = temp;

  if (print_array_at_each_step) {
    std::cout << "A[" << init_index + 1 << ":" << final_index + 1 << "]: ";
    for (int i = init_index; i < final_index + 1; i++) {
      std::cout << list_of_numbers[i] << " ";
    }

    std::cout << std::endl;
  }

  return (start + 1);
}

int QuickSort(int list_of_numbers[], int init_index, int final_index, int flag,
              int print_array_at_each_step) {
  if (init_index < final_index) {
    int mid = Partition(list_of_numbers, init_index, final_index, flag,
                        print_array_at_each_step);
    QuickSort(list_of_numbers, init_index, mid - 1, flag,
              print_array_at_each_step);
    QuickSort(list_of_numbers, mid + 1, final_index, flag,
              print_array_at_each_step);
  }

  return count_EWC_quick;
}
