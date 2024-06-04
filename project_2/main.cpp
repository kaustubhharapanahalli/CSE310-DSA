/*
 * Copyright (C) 2022 Kaustubh Manoj Harapanahalli
 */

#include <stdio.h>
#include <stdlib.h>

#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "heap.hpp"  // NOLINT
#include "util.hpp"  // NOLINT

int main(int argc, char *argv[]) {
  FILE *fp;
  int adt, capacity, size;

  if (argc < 3) {
    fprintf(stderr,
            "Usage: ./PJ2 DataStructure Capacity\n       DataStructure should "
            "be in {MaxHeap, MinHeap, DoubleHeap}\n       Capacity must be a "
            "positive integer\n");
    exit(1);
  }

  if (strcmp(argv[1], "MaxHeap") && strcmp(argv[1], "MinHeap") &&
      strcmp(argv[1], "DoubleHeap")) {
    fprintf(stderr,
            "Usage: ./PJ2 DataStructure Capacity\n       DataStructure should "
            "be in {MaxHeap, MinHeap, DoubleHeap}\n       Capacity must be a "
            "positive integer\n");
    exit(1);
  }

  capacity = atoi(argv[2]);

  if (capacity <= 0) {
    fprintf(stderr,
            "Usage: ./PJ2 DataStructure Capacity\n       DataStructure should "
            "be in {MaxHeap, MinHeap, DoubleHeap}\n       Capacity must be a "
            "positive integer\n");
    exit(1);
  }

  if (strcmp(argv[1], "MaxHeap") == 0) {
    adt = 1;
  } else if (strcmp(argv[1], "MinHeap") == 0) {
    adt = 2;
  } else if (strcmp(argv[1], "DoubleHeap") == 0) {
    adt = 3;
  }

  fp = fopen("HEAPifile.txt", "r");
  if (fp == NULL)
    return 0;
  else
    fscanf(fp, "%d", &size);

  fclose(fp);

  HEAP heapObject;

  heapObject.capacity = capacity;
  heapObject.heap_size = 0;

  std::string inputCommand;
  size = 0;

  if (adt == 1) {
    /**************************************************
     **************************************************
     * Implementation of functions for MaxHeap
     **************************************************
     **************************************************/
    MaxHeap maxheap(&heapObject);
    std::ofstream fpwrite("HEAPofile.txt");

    fp = fopen("HEAPifile.txt", "r");
    if (fp == NULL)
      return 0;
    else
      fscanf(fp, "%d", &size);

    ELEMENT inputArray[size];  // NOLINT

    fclose(fp);

    while (true) {
      std::string tokens[3];
      std::string inputCommand;
      getline(std::cin, inputCommand);
      std::stringstream ssin(inputCommand);
      std::string command;
      std::string token;

      int i = 0;

      while (ssin.good() && i < 3) {
        ssin >> tokens[i];
        ++i;
      }

      command = tokens[0];

      if (command == "Print") {
        if (heapObject.heap_size <= 0) {
          std::cout << "capacity=" << heapObject.capacity << ", "
                    << "size=" << heapObject.heap_size << std::endl;
        } else {
          std::cout << "capacity=" << heapObject.capacity << ", "
                    << "size=" << heapObject.heap_size << std::endl;

          std::cout << "MaxHeap: " << std::flush;
          for (int i = 1; i <= heapObject.heap_size - 1; i++) {
            std::cout << heapObject.A[i].value << ", " << std::flush;
          }
          std::cout << (heapObject.A)[heapObject.heap_size].value << std::endl;
        }

      } else if (command == "Read") {
        fp = fopen("HEAPifile.txt", "r");
        if (fp == NULL) {
          fprintf(stderr, "Error: Cannot open file HEAPifile.txt\n");
          continue;
        }

        fscanf(fp, "%d", &size);

        if (size > heapObject.capacity) {
          fprintf(stderr, "Error: Cannot allocate memory for heap\n");
          fclose(fp);
          continue;
        }

        if (size <= 0) {
          fprintf(stderr, "Error: Cannot allocate memory for heap\n");
          continue;
        }

        for (int i = 1; i <= size; i++) {
          inputArray[i].key = i;
          inputArray[i].index = i;
          fscanf(fp, "%d", &inputArray[i].value);
        }
        fclose(fp);
        heapObject.element_count = size;
        heapObject.A = inputArray;
        heapObject.heap_size = size;

        maxheap.BuildHeap();

      } else if (command == "Write") {
        if (fp == NULL) {
          fprintf(stderr, "Error: Cannot open file HEAPofile.txt\n");
          continue;
        }

        fpwrite << "capacity=" << heapObject.capacity
                << ", size=" << heapObject.heap_size << std::endl;

        std::string msg;

        fpwrite << "MaxHeap: " << std::flush;
        for (int i = 1; i <= heapObject.heap_size - 1; i++) {
          fpwrite << inputArray[i].value << ", " << std::flush;
        }
        fpwrite << inputArray[heapObject.heap_size].value << std::endl;

      } else if (command == "Insert") {
        if (tokens[1] == "") {
          fprintf(stderr, "Error: Invalid command\n");
          continue;
        }

        if (heapObject.heap_size >= heapObject.capacity) {
          fprintf(stderr, "Error: Insertion to a null/full heap\n");
          continue;
        }

        maxheap.Insert(std::stoi(tokens[1]));

      } else if (command == "ExtractMax") {
        if (heapObject.A == NULL || heapObject.capacity <= 0 ||
            heapObject.heap_size <= 0) {
          fprintf(stderr,
                  "Error: ExtractMax in a min heap or a null/empty heap\n");
        }
        returnValue result = maxheap.ExtractMax();
        std::cout << "ExtractMax: " << result.val1 << std::endl;

      } else if (command == "IncreaseKey") {
        if (tokens[1] == "" || tokens[2] == "") {
          fprintf(stderr, "Error: Invalid command\n");
          continue;
        }
        maxheap.IncreaseKey(std::stoi(tokens[1]), std::stoi(tokens[2]));

      } else if (command == "DecreaseKey") {
        if (tokens[1] == "" || tokens[2] == "") {
          fprintf(stderr, "Error: Invalid command\n");
          continue;
        }

        fprintf(stderr,
                "Error: DecreaseKey in a max heap or a null/empty heap\n");

      } else if (command == "Delete") {
        if (tokens[1] == "") {
          fprintf(stderr, "Error: Invalid command\n");
          continue;
        }
        std::string index;
        ssin >> index;

        int deleteValue = maxheap.Delete(std::stoi(tokens[1]));

        std::cout << "Delete: " << deleteValue << std::endl;

      } else if (command == "Stop") {
        exit(1);

      } else if (command == "ExtractMin") {
        fprintf(stderr,
                "Error: ExtractMin in a max heap or a null/empty heap\n");
        continue;
      } else {
        fprintf(stderr, "Invalid command\n");
        continue;
      }
    }
    fpwrite.close();

  } else if (adt == 2) {  // MIN HEAP
    /**************************************************
     **************************************************
     * Implementation of functions for MinHeap
     **************************************************
     **************************************************/
    MinHeap minheap(&heapObject);
    std::ofstream fpwrite("HEAPofile.txt");

    fp = fopen("HEAPifile.txt", "r");
    if (fp == NULL)
      return 0;
    else
      fscanf(fp, "%d", &size);

    ELEMENT inputArray[size];  // NOLINT

    fclose(fp);

    while (true) {
      std::string tokens[3];
      std::string inputCommand;
      getline(std::cin, inputCommand);
      std::stringstream ssin(inputCommand);
      std::string command;
      std::string token;

      int i = 0;

      while (ssin.good() && i < 3) {
        ssin >> tokens[i];
        ++i;
      }

      command = tokens[0];

      if (command == "Print") {
        if (heapObject.heap_size <= 0) {
          std::cout << "capacity=" << heapObject.capacity << ", "
                    << "size=" << heapObject.heap_size << std::endl;
        } else {
          std::cout << "capacity=" << heapObject.capacity << ", "
                    << "size=" << heapObject.heap_size << std::endl;

          std::cout << "MinHeap: " << std::flush;
          for (int i = 1; i <= heapObject.heap_size - 1; i++) {
            std::cout << heapObject.A[i].value << ", " << std::flush;
          }
          std::cout << (heapObject.A)[heapObject.heap_size].value << std::endl;
        }

      } else if (command == "Read") {
        fp = fopen("HEAPifile.txt", "r");
        if (fp == NULL) {
          fprintf(stderr, "Error: Cannot open file HEAPifile.txt\n");
          continue;
        }

        fscanf(fp, "%d", &size);

        if (size > heapObject.capacity) {
          fprintf(stderr, "Error: Cannot allocate memory for heap\n");
          fclose(fp);
          continue;
        }

        if (size == 0) {
          fprintf(stderr, "Error: Cannot allocate memory for heap\n");
          continue;
        }

        for (int i = 1; i <= size; i++) {
          inputArray[i].key = i;
          inputArray[i].index = i;
          fscanf(fp, "%d", &inputArray[i].value);
        }

        fclose(fp);
        heapObject.element_count = size;
        heapObject.A = inputArray;
        heapObject.heap_size = size;

        minheap.BuildHeap();

      } else if (command == "Write") {
        if (fp == NULL) {
          fprintf(stderr, "Error: Cannot open file HEAPofile.txt\n");
          continue;
        }

        fpwrite << "capacity=" << heapObject.capacity
                << ", size=" << heapObject.heap_size << std::endl;

        std::string msg;

        fpwrite << "MinHeap: " << std::flush;
        for (int i = 1; i <= heapObject.heap_size - 1; i++) {
          fpwrite << inputArray[i].value << ", " << std::flush;
        }
        fpwrite << inputArray[heapObject.heap_size].value << std::endl;

      } else if (command == "Insert") {
        if (tokens[1] == "") {
          fprintf(stderr, "Error: Invalid command\n");
          continue;
        }

        if (heapObject.heap_size >= heapObject.capacity) {
          fprintf(stderr, "Error: Insertion to a null/full heap\n");
          continue;
        }

        minheap.Insert(std::stoi(tokens[1]));

      } else if (command == "ExtractMin") {
        if (heapObject.A == NULL || heapObject.capacity <= 0 ||
            heapObject.heap_size <= 0) {
          fprintf(stderr,
                  "Error: ExtractMin in a max heap or a null/empty heap\n");
        }

        returnValue minValue = minheap.ExtractMin();
        std::cout << "ExtractMin: " << minValue.val1 << std::endl;

      } else if (command == "IncreaseKey") {
        if (tokens[1] == "" || tokens[2] == "") {
          fprintf(stderr, "Error: Invalid command\n");
          continue;
        }

        fprintf(stderr,
                "Error: IncreaseKey in a min heap or a null/empty heap\n");

      } else if (command == "DecreaseKey") {
        if (tokens[1] == "" || tokens[2] == "") {
          fprintf(stderr, "Error: Invalid command\n");
          continue;
        }

        std::string decreaseValue, index;
        ssin >> index;
        ssin >> decreaseValue;

        minheap.DecreaseKey(std::stoi(tokens[1]), std::stoi(tokens[2]));

      } else if (command == "Delete") {
        if (tokens[1] == "") {
          fprintf(stderr, "Error: Invalid command\n");
          continue;
        }
        std::string index;
        ssin >> index;

        int deleteValue = minheap.Delete(std::stoi(tokens[1]));

        std::cout << "Delete: " << deleteValue << std::endl;

      } else if (command == "Stop") {
        exit(1);

      } else if (command == "ExtractMax") {
        fprintf(stderr,
                "Error: ExtractMax in a min heap or a null/empty heap\n");
        continue;

      } else {
        fprintf(stderr, "Invalid command\n");
        continue;
      }
    }
    fpwrite.close();

  } else if (adt == 3) {
    /**************************************************
     **************************************************
     * Implementation of functions for DoubleHeap
     **************************************************
     **************************************************/

    HEAP heapObjectMinHeap;
    HEAP heapObjectMaxHeap;

    heapObjectMinHeap.capacity = capacity;
    heapObjectMinHeap.heap_size = 0;

    heapObjectMaxHeap.capacity = capacity;
    heapObjectMaxHeap.heap_size = 0;

    MinHeap minheap(&heapObjectMinHeap);
    MaxHeap maxheap(&heapObjectMaxHeap);

    std::ofstream fpwrite("HEAPofile.txt");

    fp = fopen("HEAPifile.txt", "r");
    if (fp == NULL)
      return 0;
    else
      fscanf(fp, "%d", &size);

    ELEMENT inputArrayMinHeap[size];  // NOLINT
    ELEMENT inputArrayMaxHeap[size];  // NOLINT

    fclose(fp);

    while (true) {
      std::string tokens[3];
      std::string inputCommand;
      getline(std::cin, inputCommand);
      std::stringstream ssin(inputCommand);
      std::string command;
      std::string token;

      int i = 0;

      while (ssin.good() && i < 3) {
        ssin >> tokens[i];
        ++i;
      }

      command = tokens[0];

      if (command == "Print") {
        if (heapObjectMaxHeap.heap_size <= 0 &&
            heapObjectMinHeap.heap_size <= 0) {
          std::cout << "capacity=" << heapObjectMaxHeap.capacity << ", "
                    << "size=" << heapObjectMaxHeap.heap_size << std::endl;
        } else {
          std::cout << "capacity=" << heapObjectMaxHeap.capacity << ", "
                    << "size=" << heapObjectMaxHeap.heap_size << std::endl;

          std::cout << "MaxHeap: " << std::flush;
          for (int i = 1; i <= heapObjectMaxHeap.heap_size - 1; i++) {
            std::cout << heapObjectMaxHeap.A[i].value << ", " << std::flush;
          }
          std::cout << (heapObjectMaxHeap.A)[heapObjectMaxHeap.heap_size].value
                    << std::endl;

          std::cout << "MinHeap: " << std::flush;
          for (int i = 1; i <= heapObjectMinHeap.heap_size - 1; i++) {
            std::cout << heapObjectMinHeap.A[i].value << ", " << std::flush;
          }
          std::cout << (heapObjectMinHeap.A)[heapObjectMinHeap.heap_size].value
                    << std::endl;
        }

      } else if (command == "Read") {
        fp = fopen("HEAPifile.txt", "r");
        if (fp == NULL) {
          fprintf(stderr, "Error: Cannot open file HEAPifile.txt\n");
          continue;
        }

        fscanf(fp, "%d", &size);

        if (size > heapObject.capacity) {
          fprintf(stderr, "Error: Cannot allocate memory for heap\n");
          fclose(fp);
          continue;
        }

        if (size == 0) {
          fprintf(stderr, "Error: Cannot allocate memory for heap\n");
          continue;
        }

        for (int i = 1; i <= size; i++) {
          inputArrayMaxHeap[i].key = i;
          inputArrayMaxHeap[i].index = i;
          fscanf(fp, "%d", &inputArrayMaxHeap[i].value);
        }
        fclose(fp);
        heapObjectMaxHeap.element_count = size;
        heapObjectMaxHeap.A = inputArrayMaxHeap;
        heapObjectMaxHeap.heap_size = size;

        maxheap.BuildHeap();

        fp = fopen("HEAPifile.txt", "r");
        if (fp == NULL) {
          fprintf(stderr, "Error: Cannot open file HEAPifile.txt\n");
          continue;
        }

        fscanf(fp, "%d", &size);

        if (size > heapObjectMinHeap.capacity) {
          fprintf(stderr, "Error: Cannot allocate memory for heap\n");
          fclose(fp);
          continue;
        }

        if (size == 0) {
          fprintf(stderr, "Error: Cannot allocate memory for min heap array\n");
          continue;
        }

        for (int i = 1; i <= size; i++) {
          inputArrayMinHeap[i].key = i;
          inputArrayMinHeap[i].index = i;
          fscanf(fp, "%d", &inputArrayMinHeap[i].value);
        }
        fclose(fp);
        heapObjectMinHeap.element_count = size;
        heapObjectMinHeap.A = inputArrayMinHeap;
        heapObjectMinHeap.heap_size = size;

        minheap.BuildHeap();

      } else if (command == "Write") {
        if (fp == NULL) {
          fprintf(stderr, "Error: Cannot open file HEAPofile.txt\n");
          continue;
        }

        fpwrite << "capacity=" << heapObjectMinHeap.capacity
                << ", size=" << heapObjectMinHeap.heap_size << std::endl;

        std::string msg;

        fpwrite << "MaxHeap: " << std::flush;
        for (int i = 1; i <= heapObjectMinHeap.heap_size - 1; i++) {
          fpwrite << inputArrayMaxHeap[i].value << ", " << std::flush;
        }
        fpwrite << inputArrayMaxHeap[heapObjectMinHeap.heap_size].value
                << std::endl;

        fpwrite << "MinHeap: " << std::flush;
        for (int i = 1; i <= heapObjectMinHeap.heap_size - 1; i++) {
          fpwrite << inputArrayMinHeap[i].value << ", " << std::flush;
        }
        fpwrite << inputArrayMinHeap[heapObjectMinHeap.heap_size].value
                << std::endl;

      } else if (command == "Insert") {
        if (tokens[1] == "") {
          fprintf(stderr, "Error: Invalid command\n");
          continue;
        }

        if (heapObjectMinHeap.heap_size >= heapObjectMinHeap.capacity ||
            heapObjectMaxHeap.heap_size >= heapObjectMaxHeap.capacity) {
          fprintf(stderr, "Error: Insertion to a null/full heap\n");
          continue;
        }

        maxheap.Insert(std::stoi(tokens[1]));
        minheap.Insert(std::stoi(tokens[1]));

      } else if (command == "ExtractMax") {
        if (heapObjectMaxHeap.A == NULL || heapObjectMaxHeap.capacity <= 0 ||
            heapObjectMaxHeap.heap_size <= 0) {
          fprintf(stderr,
                  "Error: ExtractMax in a min heap or a null/empty heap\n");
        }
        PriorityQueue priority_queue;

        int min_key = heapObjectMaxHeap.A[1].key;

        returnValue result = maxheap.ExtractMax();
        std::cout << "ExtractMax: " << result.val1 << std::endl;

        int index = 0;
        for (int i = 1; i <= heapObjectMinHeap.heap_size; i++) {
          if (heapObjectMinHeap.A[i].key == min_key) {
            heapObjectMinHeap.A[i].key =
                heapObjectMinHeap.A[heapObjectMinHeap.heap_size].key;
            heapObjectMinHeap.A[i].value =
                heapObjectMinHeap.A[heapObjectMinHeap.heap_size].value;
            index = heapObjectMinHeap.A[i].index;
            heapObjectMinHeap.heap_size--;
          }
        }

        if (index > 1 && index <= heapObjectMinHeap.heap_size &&
            heapObjectMinHeap.A[index].value <
                heapObjectMinHeap.A[index / 2].value) {
          while (index > 1 && heapObjectMinHeap.A[index].value <
                                  heapObjectMinHeap.A[index / 2].value) {
            priority_queue.Swap(heapObjectMinHeap.A, index, index / 2);
            index = index / 2;
          }
        } else {
          minheap.MinHeapify(heapObjectMinHeap.A, index);
        }
      } else if (command == "ExtractMin") {
        if (heapObjectMinHeap.A == NULL || heapObjectMinHeap.capacity <= 0 ||
            heapObjectMinHeap.heap_size <= 0) {
          fprintf(stderr,
                  "Error: ExtractMin in a max heap or a null/empty heap\n");
        }
        PriorityQueue priority_queue;

        returnValue result = minheap.ExtractMin();
        std::cout << "ExtractMin: " << result.val1 << std::endl;

        int index = result.val2;

        for (int i = 1; i <= heapObjectMaxHeap.heap_size; i++) {
          if (heapObjectMaxHeap.A[i].key == result.val2) {
            heapObjectMaxHeap.A[i].key =
                heapObjectMaxHeap.A[heapObjectMaxHeap.heap_size].key;
            heapObjectMaxHeap.A[i].value =
                heapObjectMaxHeap.A[heapObjectMaxHeap.heap_size].value;

            index = heapObjectMaxHeap.A[i].index;
            heapObjectMaxHeap.heap_size--;
          }
        }

        if (index > 1 && index <= heapObjectMaxHeap.heap_size &&
            heapObjectMaxHeap.A[index].value >
                heapObjectMaxHeap.A[index / 2].value) {
          while (index > 1 && heapObjectMaxHeap.A[index].value >
                                  heapObjectMaxHeap.A[index / 2].value) {
            priority_queue.Swap(heapObjectMaxHeap.A, index, index / 2);
            index = index / 2;
          }
        } else {
          maxheap.MaxHeapify(heapObjectMaxHeap.A, index);
        }

      } else if (command == "IncreaseKey") {
        if (tokens[1] == "" || tokens[2] == "") {
          fprintf(stderr, "Error: Invalid command\n");
          continue;
        }

        for (int i = 1; i <= heapObjectMinHeap.heap_size; i++) {
          if (heapObjectMinHeap.A[i].key ==
              heapObjectMaxHeap.A[std::stoi(tokens[1])].key) {
            minheap.IncreaseKey(heapObjectMinHeap.A[i].index,
                                std::stoi(tokens[2]));
            break;
          }
        }
        maxheap.IncreaseKey(std::stoi(tokens[1]), std::stoi(tokens[2]));

      } else if (command == "DecreaseKey") {
        if (tokens[1] == "" || tokens[2] == "") {
          fprintf(stderr, "Error: Invalid command\n");
          continue;
        }

        for (int i = 1; i <= heapObjectMaxHeap.heap_size; i++) {
          if (heapObjectMaxHeap.A[i].key ==
              heapObjectMinHeap.A[std::stoi(tokens[1])].key) {
            maxheap.DecreaseKey(heapObjectMaxHeap.A[i].index,
                                std::stoi(tokens[2]));
            break;
          }
        }
        minheap.DecreaseKey(std::stoi(tokens[1]), std::stoi(tokens[2]));

      } else if (command == "Stop") {
        exit(1);

      } else {
        fprintf(stderr, "Invalid command\n");
        continue;
      }
    }
    fpwrite.close();
  }

  return 0;
}  // NOLINT
