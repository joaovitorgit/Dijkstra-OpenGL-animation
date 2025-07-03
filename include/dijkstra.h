#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "graph.h"

// Function declarations for Dijkstra's algorithm
void run_dijkstra(Graph* graph);
void animate_dijkstra(Graph* graph, int* distances, int* previous, int* visited);
void highlight_shortest_path(Graph* graph, int* previous);
void delay_milliseconds(int milliseconds);

#endif // DIJKSTRA_H 