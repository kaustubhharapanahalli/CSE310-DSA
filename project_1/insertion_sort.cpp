/*
 * Copyright (C) 2022 Kaustubh Manoj Harapanahalli
 */
#include "insertion_sort.hpp"  // NOLINT

#include <algorithm>
#include <iostream>
#include <vector>

int InsertionSort(int list_of_numbers[], int number_of_elements, int flag,
                  int print_array_at_each_step) {
  int count_EWC = 0;

  for (int index_1 = 1; index_1 < number_of_elements; index_1++) {
    int key = list_of_numbers[index_1];
    int index_2 = index_1 - 1;

    if (!(list_of_numbers[index_2] > key)) {
      count_EWC++;

      if (flag) {
        std::cout << "EWC: " << list_of_numbers[index_2] << " > " << key << "?"
                  << std::endl;
      }
    }
    while (index_2 >= 0 && list_of_numbers[index_2] > key) {
      count_EWC++;

      if (flag) {
        std::cout << "EWC: " << list_of_numbers[index_2] << " > " << key << "?"
                  << std::endl;
      }

      list_of_numbers[index_2 + 1] = list_of_numbers[index_2];

      if (print_array_at_each_step) {
        std::cout << "A[1:" << number_of_elements << "]: ";
        for (int i = 0; i < number_of_elements - 1; i++) {
          std::cout << list_of_numbers[i] << " ";
        }

        std::cout << list_of_numbers[number_of_elements - 1] << std::endl;
      }
      index_2 = index_2 - 1;
    }

    list_of_numbers[index_2 + 1] = key;

    if (print_array_at_each_step) {
      std::cout << "A[1:" << number_of_elements << "]: ";
      for (int i = 0; i < number_of_elements - 1; i++) {
        std::cout << list_of_numbers[i] << " ";
      }

      std::cout << list_of_numbers[number_of_elements - 1] << std::endl;
    }
  }

  return count_EWC;
}
