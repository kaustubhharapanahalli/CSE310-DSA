// Copyright (c) 2022 - Kaustubh Harapanahalli

#ifndef GRAPH_H_
#define GRAPH_H_

#include <string>
#include <vector>

struct adjacencyListNode {
  int destination_index;
  float edge_weight;
  int predecessor;
  struct adjacencyListNode* next;
};

struct adjacencyList {
  struct adjacencyListNode* head;
};

struct graphTree {
  int vertices;
  struct adjacencyList* adjacency_list_array;
};

class Graph {
 public:
  Graph();
  struct adjacencyListNode* newAdjacencyListNode(int destination, float weight);
  struct graphTree* createGraph(int vertices);
  void addEdge(struct graphTree* graph, int source, int destination,
               float weight, bool directed_status);
  struct graphTree* createGraph(FILE* input_file, bool directed_status,
                                int vertices_count, int edge_count);
  void dijkstraSingleSource(struct graphTree* graph, int source);
  void dijkstra(struct graphTree* graph, int source, int destination,
                std::string printCommand, int parentSource);
  std::string shortestPath(struct graphTree* graph, int source,
                           int destination);
  void printPath(struct graphTree* graph, int source, int destination,
                 int parentSource);
  void printCommandExecutor(struct graphTree* graph, std::string printCommand,
                            int source, int destination, int parentSource,
                            float distance[]);
};

#endif  // GRAPH_H_
