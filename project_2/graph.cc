// Copyright (c) 2022 - Kaustubh Harapanahalli
#include "graph.h"  // NOLINT

#include <cfloat>
#include <cstring>
#include <iostream>
#include <limits>
#include <map>
#include <string>
#include <vector>

#include "minHeap.h"

minHeapIm minHeapObject;

void printArr(float dist[], int n) {
  printf("Vertex   Distance from Source\n");
  for (int i = 0; i < n; ++i) {
    printf("%d \t\t %f\n", i, dist[i]);
  }
}

struct adjacencyListNode* Graph::newAdjacencyListNode(int destination,
                                                      float edge_weight) {
  struct adjacencyListNode* new_node =
      (struct adjacencyListNode*)malloc(sizeof(struct adjacencyListNode));
  new_node->destination_index = destination;
  new_node->edge_weight = edge_weight;
  new_node->next = NULL;
  new_node->predecessor = -1;

  return new_node;
}

struct graphTree* Graph::createGraph(int vertices) {
  struct graphTree* graph = (struct graphTree*)malloc(sizeof(struct graphTree));
  graph->vertices = vertices;

  graph->adjacency_list_array =
      (struct adjacencyList*)malloc(vertices * sizeof(struct adjacencyList));

  for (int i = 0; i < vertices; ++i) {
    graph->adjacency_list_array[i].head = NULL;
  }

  return graph;
}

void Graph::addEdge(struct graphTree* graph, int source, int destination,
                    float edge_weight, bool directed_status) {
  struct adjacencyListNode* new_node =
      newAdjacencyListNode(destination, edge_weight);

  new_node->next = graph->adjacency_list_array[source].head;

  graph->adjacency_list_array[source].head = new_node;

  // If graph is undirected
  if (directed_status != false) {
    new_node = newAdjacencyListNode(source, edge_weight);
    new_node->next = graph->adjacency_list_array[destination].head;
    graph->adjacency_list_array[destination].head = new_node;
  }
}

Graph::Graph() {}

struct graphTree* Graph::createGraph(FILE* input_file, bool directed_status,
                                     int vertices_count, int edge_count) {
  struct graphTree* graph = createGraph(vertices_count);

  for (int i = 0; i < edge_count; i++) {
    int edge_index, start_vertex, termination_vertex;
    float edge_weight;
    fscanf(input_file, "%d", &edge_index);
    fscanf(input_file, "%d", &start_vertex);
    fscanf(input_file, "%d", &termination_vertex);
    fscanf(input_file, "%f", &edge_weight);

    addEdge(graph, start_vertex - 1, termination_vertex - 1, edge_weight,
            directed_status);
  }

  return graph;
}

void Graph::dijkstraSingleSource(struct graphTree* graph, int source) {
  int kVertices = graph->vertices;
  float distance[kVertices];
  struct heap* minheap = minHeapObject.createMinHeap(kVertices);
  graph->adjacency_list_array[source].head->predecessor = -1;

  for (int vertex = 0; vertex < kVertices; vertex++) {
    distance[vertex] = FLT_MAX;
    minheap->array[vertex] =
        minHeapObject.newMinHeapNode(vertex, distance[vertex]);
    minheap->position[vertex] = vertex;
  }

  minheap->array[source] =
      minHeapObject.newMinHeapNode(source, distance[source]);
  minheap->position[source] = source;
  distance[source] = 0;
  minHeapObject.decreaseKey(minheap, source, distance[source]);

  minheap->size = kVertices;
  while (!minHeapObject.isEmpty(minheap)) {
    struct heapNode* minheapnode = minHeapObject.extractMin(minheap);

    int u = minheapnode->value;

    struct adjacencyListNode* pCrawl = graph->adjacency_list_array[u].head;

    while (pCrawl != NULL) {
      int v = pCrawl->destination_index;

      if (pCrawl->edge_weight + distance[u] < distance[v]) {
        distance[v] = distance[u] + pCrawl->edge_weight;
        graph->adjacency_list_array[v].head->predecessor = u;

        minHeapObject.decreaseKey(minheap, v, distance[v]);
      }
      pCrawl = pCrawl->next;
    }
  }
  // printArr(distance, kVertices);
}

void Graph::dijkstra(struct graphTree* graph, int source, int destination,
                     std::string printCommand, int parentSource) {
  int kVertices = graph->vertices;
  float distance[kVertices];
  struct heap* minheap = minHeapObject.createMinHeap(kVertices);
  // std::cout << "source: " << source << " - destination: " << destination
  //           << std::endl;

  graph->adjacency_list_array[source].head->predecessor = -1;
  for (int vertex = 0; vertex < kVertices; vertex++) {
    distance[vertex] = FLT_MAX;
    minheap->array[vertex] =
        minHeapObject.newMinHeapNode(vertex, distance[vertex]);
    minheap->position[vertex] = vertex;
  }
  // std::cout << "Source: " << source << std::endl;
  minheap->array[source] =
      minHeapObject.newMinHeapNode(source, distance[source]);
  minheap->position[source] = source;
  distance[source] = 0;
  minHeapObject.decreaseKey(minheap, source, distance[source]);

  minheap->size = kVertices;
  while (!minHeapObject.isEmpty(minheap)) {
    struct heapNode* minheapnode = minHeapObject.extractMin(minheap);

    int u = minheapnode->value;
    // std::cout << u << std::endl;
    struct adjacencyListNode* pCrawl = graph->adjacency_list_array[u].head;

    while (pCrawl != NULL) {
      int v = pCrawl->destination_index;
      // bool x = minHeapObject.isInMinHeap(minheap, v);
      // std::cout << x << std::flush;
      // bool y = distance[u] != FLT_MAX;
      // std::cout << y << std::flush;
      // bool z = pCrawl->edge_weight + distance[u] < distance[v];
      // std::cout << z << std::endl;
      if (pCrawl->edge_weight + distance[u] < distance[v]) {
        // std::cout << u << std::endl;
        distance[v] = distance[u] + pCrawl->edge_weight;
        graph->adjacency_list_array[v].head->predecessor = u;

        minHeapObject.decreaseKey(minheap, v, distance[v]);
      }
      pCrawl = pCrawl->next;
    }
  }

  // printArr(distance, kVertices);

  if (printCommand != "None") {
    printCommandExecutor(graph, printCommand, source, destination, parentSource,
                         distance);
  }
}

void Graph::printCommandExecutor(struct graphTree* graph,
                                 std::string printCommand, int source,
                                 int destination, int parentSource,
                                 float distance[]) {
  if (printCommand == "PrintLength") {
    if (distance[destination] == FLT_MAX) {
      if (parentSource != source) {
      } else {
        fprintf(stdout, "There is no path from %d to %d.\n", source + 1,
                destination + 1);
      }
    } else if (parentSource == source) {
      fprintf(stdout,
              "The length of the shortest path from %d to %d is: %8.2f\n",
              source + 1, destination + 1, distance[destination]);
    }
  } else if (printCommand == "PrintPath") {
    std::vector<int> path_vertices;
    // for (int i = 0; i < graph->vertices; i++) {
    //   std::cout << "Node: " << i << " - Predecessor: "
    //             << graph->adjacency_list_array[i].head->predecessor
    //             << std::endl;
    // }
    // std::cout << "source: " << source << " - parentSource: " << parentSource
    //           << std::endl;
    if (source == destination) {
      fprintf(stdout, "The shortest path from %d to %d is:\n", source + 1,
              destination + 1);
      fprintf(stdout, "[%d:%8.2f].\n", source + 1, distance[source]);

    } else if (graph->adjacency_list_array[destination].head->predecessor ==
                   -1 &&
               parentSource == source) {
      fprintf(stdout, "There is no path from %d to %d.\n", source + 1,
              destination + 1);

    } else if (parentSource == source) {
      struct adjacencyListNode* pCrawl =
          graph->adjacency_list_array[destination].head;

      path_vertices.push_back(destination);

      while (pCrawl->predecessor != -1) {
        // std::cout << "Pred: " << pCrawl->predecessor << std::endl;
        path_vertices.push_back(pCrawl->predecessor);
        pCrawl = graph->adjacency_list_array[pCrawl->predecessor].head;
      }

      // std::cout << path_vertices.size() << std::endl;
      // for (int i = path_vertices.size() - 1; i >= 0; --i) {
      //   std::cout << path_vertices[i] << std::endl;
      // }

      fprintf(stdout, "The shortest path from %d to %d is:\n", source + 1,
              destination + 1);
      fprintf(stdout, "[%d:%8.2f]", source + 1, distance[source]);
      for (int i = path_vertices.size() - 2; i >= 0; i--) {
        int index = path_vertices[i];
        fprintf(stdout, "-->[%d:%8.2f]", path_vertices[i] + 1, distance[index]);
      }
      std::cout << "." << std::endl;
    } else {
    }
  }
}

// void Graph::printPath(struct graphTree* graph, int source, int
// destination,
//                       int parentSource) {
//   // float* distance = dijkstra(graph, source);

//   printf("Vertex   Distance from Source\n");
//   for (int i = 0; i < graph->vertices; ++i) {
//     printf("%d \t\t %f\n", i, distance[i]);
//   }

//   std::vector<int> path_vertices;

//   if (graph->adjacency_list_array[destination].head->predecessor == -1) {
//     fprintf(stdout, "There is no path from %d to %d.\n", source + 1,
//             destination + 1);

//   } else if (parentSource == source) {
//     struct adjacencyListNode* pCrawl =
//         graph->adjacency_list_array[destination].head;

//     path_vertices.push_back(destination + 1);
//     std::cout << "Dest: " << destination + 1 << std::endl;

//     while (pCrawl->predecessor != -1) {
//       std::cout << "Pred: " << pCrawl->predecessor << std::endl;
//       path_vertices.push_back(pCrawl->predecessor);
//       pCrawl = graph->adjacency_list_array[pCrawl->predecessor].head;
//     }

//     fprintf(stdout, "The shortest path from %d to %d is:\n", source + 1,
//             destination + 1);
//     fprintf(stdout, "[%d:%8.2f]", source + 1, distance[destination]);
//     for (int i = path_vertices.size() - 1; i > 0; i--) {
//       int index = path_vertices[i];
//       fprintf(stdout, "-->[%d:%8.2f]", path_vertices[i],
//       distance[index]);
//     }
//     std::cout << "." << std::endl;
//   }

//   for (int i = 0; i < graph->vertices; i++) {
//     std::cout << "Node: " << i << " - Predecessor: "
//               << graph->adjacency_list_array[i].head->predecessor <<
//               std::endl;
//   }
// }

/*****************************************************
 *****************************************************
 * Min heap implementation for the initial version.
 *****************************************************
 *****************************************************/
/*****************************************************
 *****************************************************
 * Min heap implementation for the initial version.
 *****************************************************
 *****************************************************/
/*****************************************************
 *****************************************************
 * Min heap implementation for the initial version.
 *****************************************************
 *****************************************************/

std::string Graph::shortestPath(struct graphTree* graph, int source,
                                int destination) {
  int kVertices = graph->vertices;
  float distance[kVertices];
  // graph->adjacency_list_array[source].head->predecessor = NULL;
  // std::map<int, std::vector<int>> path;

  struct heap* minheap = minHeapObject.createMinHeap(kVertices);

  for (int vertex = 0; vertex < kVertices; vertex++) {
    distance[vertex] = FLT_MAX;
    minheap->array[vertex] =
        minHeapObject.newMinHeapNode(vertex, distance[vertex]);
    minheap->position[vertex] = vertex;
  }

  minheap->array[source] =
      minHeapObject.newMinHeapNode(source, distance[source]);
  minheap->position[source] = source;
  distance[source] = 0;
  minHeapObject.decreaseKey(minheap, source, distance[source]);

  // Building predecessor tree for source

  minheap->size = kVertices;
  while (!minHeapObject.isEmpty(minheap)) {
    struct heapNode* minheapnode = minHeapObject.extractMin(minheap);

    int u = minheapnode->value;

    struct adjacencyListNode* pCrawl = graph->adjacency_list_array[u].head;

    while (pCrawl != NULL) {
      int v = pCrawl->destination_index;

      if (pCrawl->edge_weight + distance[u] < distance[v]) {
        distance[v] = distance[u] + pCrawl->edge_weight;
        graph->adjacency_list_array[v].head->predecessor = u;
        minHeapObject.decreaseKey(minheap, v, distance[v]);
      }
      pCrawl = pCrawl->next;
    }
  }

  // printArr(distance, kVertices);

  return "Hello";
}
