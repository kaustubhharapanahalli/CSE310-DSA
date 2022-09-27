/*
 * Copyright (C) 2022 Kaustubh Manoj Harapanahalli
 */

#ifndef PROJECT_1_QUICK_SORT_HPP_
#define PROJECT_1_QUICK_SORT_HPP_

#include <vector>

int QuickSort(int list_of_numbers[], int init_index, int final_index, int flag,
              int print_array_at_each_step);
int Partition(int list_of_numbers[], int init_index, int final_index, int flag,
              int print_array_at_each_step);

#endif  // PROJECT_1_QUICK_SORT_HPP_
