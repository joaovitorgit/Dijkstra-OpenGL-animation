#ifndef GRAPH_H
#define GRAPH_H

#include "constants.h"

// Node structure representing a vertex in the graph
typedef struct {
    int id;
    int x;
    int y;
} Node;

// Graph structure containing all graph data
typedef struct {
    Node nodes[MAX_VERTICES];
    int adjacency_matrix[MAX_VERTICES][MAX_VERTICES];
    int node_count;
    Node source;
    Node destination;
    int source_defined;
    int destination_defined;
} Graph;

// Function declarations
void init_graph(Graph* graph);
int calculate_distance(Node a, Node b);
int find_nearest_node(int* distances, int* visited, int node_count);
int is_node_at_position(Graph* graph, int x, int y);
Node* get_node_at_position(Graph* graph, int x, int y);
void add_node(Graph* graph, int x, int y);
void add_edge(Graph* graph, Node* node1, Node* node2);
void set_source(Graph* graph, Node* node);
void set_destination(Graph* graph, Node* node);
int is_valid_graph_for_dijkstra(Graph* graph);

#endif // GRAPH_H 