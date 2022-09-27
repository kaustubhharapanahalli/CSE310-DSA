// /*
//  * Copyright (C) 2022 Kaustubh Manoj Harapanahalli
//  */
#include "merge_sort.hpp"  // NOLINT

#include <iostream>

int count_EWC = 0;

int Merge(int list_of_numbers[], int const init_index, int const partition,
          int const final_index, int flag, int print_array_at_each_step) {
  int const sub_array_left = partition - init_index + 1;
  int const sub_array_right = final_index - partition;

  int *left_array = new int[sub_array_left - 1],
      *right_array = new int[sub_array_right - 1];

  for (int i = 0; i < sub_array_left; i++) {
    left_array[i] = list_of_numbers[init_index + i];
  }

  for (int j = 0; j < sub_array_right; j++) {
    right_array[j] = list_of_numbers[partition + 1 + j];
  }

  int sub_array_left_index = 0, sub_array_right_index = 0,
      merged_array_index = init_index;

  while (sub_array_left_index < sub_array_left &&
         sub_array_right_index < sub_array_right) {
    if (left_array[sub_array_left_index] <=
        right_array[sub_array_right_index]) {
      count_EWC++;

      if (flag) {
        std::cout << "EWC: " << left_array[sub_array_left_index]
                  << " <= " << right_array[sub_array_right_index] << "?"
                  << std::endl;
      }

      list_of_numbers[merged_array_index] = left_array[sub_array_left_index];

      if (print_array_at_each_step) {
        std::cout << "A[" << init_index + 1 << ":" << final_index + 1 << "]: ";
        for (int i = init_index; i < final_index + 1; i++) {
          std::cout << list_of_numbers[i] << " ";
        }

        std::cout << std::endl;
      }

      sub_array_left_index++;
    } else {
      count_EWC++;

      if (flag) {
        std::cout << "EWC: " << left_array[sub_array_left_index]
                  << " <= " << right_array[sub_array_right_index] << "?"
                  << std::endl;
      }

      list_of_numbers[merged_array_index] = right_array[sub_array_right_index];

      if (print_array_at_each_step) {
        std::cout << "A[" << init_index + 1 << ":" << final_index + 1 << "]: ";
        for (int i = init_index; i < final_index + 1; i++) {
          std::cout << list_of_numbers[i] << " ";
        }

        std::cout << std::endl;
      }

      sub_array_right_index++;
    }
    merged_array_index++;
  }

  while (sub_array_left_index < sub_array_left) {
    list_of_numbers[merged_array_index] = left_array[sub_array_left_index];
    sub_array_left_index++;
    merged_array_index++;

    if (print_array_at_each_step) {
      std::cout << "A[" << init_index + 1 << ":" << final_index + 1 << "]: ";
      for (int i = init_index; i < final_index + 1; i++) {
        std::cout << list_of_numbers[i] << " ";
      }

      std::cout << std::endl;
    }
  }

  while (sub_array_right_index < sub_array_right) {
    list_of_numbers[merged_array_index] = right_array[sub_array_right_index];
    sub_array_left_index++;
    merged_array_index++;

    if (print_array_at_each_step) {
      std::cout << "A[" << init_index + 1 << ":" << final_index + 1 << "]: ";
      for (int i = init_index; i < final_index + 1; i++) {
        std::cout << list_of_numbers[i] << " ";
      }

      std::cout << std::endl;
    }
  }

  delete[] left_array;
  delete[] right_array;

  return count_EWC;
}

int MergeSort(int list_of_numbers[], int const init_index,
              int const final_index, int flag, int print_array_at_each_step) {
  if (init_index >= final_index) {
    return 0;
  }

  int partition = init_index + (final_index - init_index) / 2;
  MergeSort(list_of_numbers, init_index, partition, flag,
            print_array_at_each_step);
  MergeSort(list_of_numbers, partition + 1, final_index, flag,
            print_array_at_each_step);
  Merge(list_of_numbers, init_index, partition, final_index, flag,
        print_array_at_each_step);

  return count_EWC;
}
