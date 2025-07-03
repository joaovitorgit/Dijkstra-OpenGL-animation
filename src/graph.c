#include "../include/graph.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void init_graph(Graph* graph) {
    graph->node_count = 0;
    graph->source_defined = 0;
    graph->destination_defined = 0;
    
    // Initialize adjacency matrix with infinity distances
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            graph->adjacency_matrix[i][j] = INFINITY_DISTANCE;
        }
    }
}

int calculate_distance(Node a, Node b) {
    return (int) sqrt(pow(abs(a.x - b.x), 2) + pow(abs(a.y - b.y), 2));
}

int find_nearest_node(int* distances, int* visited, int node_count) {
    int nearest_node = -1;
    int min_distance = INFINITY_DISTANCE;

    for (int i = 0; i < node_count; i++) {
        if (visited[i] != 1 && distances[i] < min_distance) {
            nearest_node = i;
            min_distance = distances[i];
        }
    }

    return nearest_node;
}

int is_node_at_position(Graph* graph, int x, int y) {
    if (graph->node_count == 0) {
        return 0;
    }

    Node temp = {graph->node_count, x, y};

    for (int i = 0; i < graph->node_count; i++) {
        if (calculate_distance(temp, graph->nodes[i]) < 2 * NODE_RADIUS) {
            return 1;
        }
    }
    return 0;
}

Node* get_node_at_position(Graph* graph, int x, int y) {
    if (graph->node_count == 0) {
        return NULL;
    }

    Node temp = {graph->node_count, x, y};

    for (int i = 0; i < graph->node_count; i++) {
        if (calculate_distance(temp, graph->nodes[i]) < 2 * NODE_RADIUS) {
            return &graph->nodes[i];
        }
    }
    return NULL;
}

void add_node(Graph* graph, int x, int y) {
    if (graph->node_count >= MAX_VERTICES) {
        return;
    }

    graph->nodes[graph->node_count].id = graph->node_count;
    graph->nodes[graph->node_count].x = x;
    graph->nodes[graph->node_count].y = y;
    graph->node_count++;
}

void add_edge(Graph* graph, Node* node1, Node* node2) {
    int distance = calculate_distance(*node1, *node2);
    graph->adjacency_matrix[node1->id][node2->id] = distance;
    graph->adjacency_matrix[node2->id][node1->id] = distance;
}

void set_source(Graph* graph, Node* node) {
    graph->source = *node;
    graph->source_defined = 1;
}

void set_destination(Graph* graph, Node* node) {
    graph->destination = *node;
    graph->destination_defined = 1;
}

int is_valid_graph_for_dijkstra(Graph* graph) {
    return graph->source_defined && graph->destination_defined;
} 