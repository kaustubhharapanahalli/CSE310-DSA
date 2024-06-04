// Copyright (c) 2022 - Kaustubh Harapanahalli
#include <stdio.h>

#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

#include "graph.h"    // NOLINT
#include "minHeap.h"  // NOLINT

int main(int argc, char *argv[]) {
  FILE *network_file;
  int vertices_count, edge_count;
  bool directed_status;
  int parentSource;

  std::string adj_output;

  if (argc < 3) {
    fprintf(stderr,
            "Usage: ./PJ2 GraphType InputFile\n       GraphType should "
            "be in {Directed, Undirected}\n       InputFile should be the "
            "exact name of the input file\n");
    exit(1);
  }

  if (strcmp(argv[1], "Directed") && strcmp(argv[1], "Undirected")) {
    fprintf(stderr,
            "Usage: ./PJ2 GraphType InputFile\n       GraphType should "
            "be in {Directed, Undirected}\n       InputFile should be the "
            "exact name of the input file\n");
    exit(1);
  }

  if (strcmp(argv[1], "Directed")) {
    directed_status = true;
  } else if (strcmp(argv[1], "Undirected")) {
    directed_status = false;
  }

  network_file = fopen(argv[2], "r");
  if (network_file == NULL) {
    return 0;
  } else {
    fscanf(network_file, "%d", &vertices_count);
    fscanf(network_file, "%d", &edge_count);
  }

  Graph graphObject;

  struct graphTree *graph_tree;
  graph_tree = graphObject.createGraph(network_file, directed_status,
                                       vertices_count, edge_count);

  fclose(network_file);

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

    if (command == "SinglePair") {
      int source = std::stoi(tokens[1]) - 1;
      int destination = std::stoi(tokens[2]) - 1;
      parentSource = source;
      std::string val =
          graphObject.shortestPath(graph_tree, source, destination);

    } else if (command == "SingleSource") {
      int source = std::stoi(tokens[1]) - 1;
      parentSource = source;
      graphObject.dijkstraSingleSource(graph_tree, source);

    } else if (command == "PrintPath") {
      int source = std::stoi(tokens[1]) - 1;
      int destination = std::stoi(tokens[2]) - 1;
      graphObject.dijkstra(graph_tree, source, destination, command,
                           parentSource);

    } else if (command == "PrintADJ") {
      for (int i = 0; i < graph_tree->vertices; i++) {
        struct adjacencyListNode *pCrawl =
            graph_tree->adjacency_list_array[i].head;
        printf("ADJ[%d]:", i + 1);
        while (pCrawl != NULL) {
          printf("-->[%d %d: %4.2f]", i + 1, pCrawl->destination_index + 1,
                 pCrawl->edge_weight);
          pCrawl = pCrawl->next;
        }
        printf("\n");
      }

    } else if (command == "PrintLength") {
      int source = std::stoi(tokens[1]) - 1;
      int destination = std::stoi(tokens[2]) - 1;
      graphObject.dijkstra(graph_tree, source, destination, command,
                           parentSource);

    } else if (command == "Stop") {
      exit(1);
    } else {
      fprintf(stderr, "Invalid Command");
    }
  }
}
