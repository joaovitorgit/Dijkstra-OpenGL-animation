#include "../include/dijkstra.h"
#include "../include/renderer.h"
#include <time.h>
#include <stdio.h>

void delay_milliseconds(int milliseconds) {
    clock_t start_time = clock();
    while (clock() < start_time + milliseconds);
}

void run_dijkstra(Graph* graph) {
    if (!is_valid_graph_for_dijkstra(graph)) {
        printf("Source and destination nodes must be defined\n");
        return;
    }

    int distances[MAX_VERTICES];
    int previous[MAX_VERTICES];
    int visited[MAX_VERTICES];

    // Initialize arrays
    for (int i = 0; i < graph->node_count; i++) {
        distances[i] = INFINITY_DISTANCE;
        previous[i] = -1;
        visited[i] = -1;
    }

    // Set source distance to 0
    distances[graph->source.id] = 0;

    // Main Dijkstra algorithm loop
    for (int i = 0; i < graph->node_count; i++) {
        int current_node = find_nearest_node(distances, visited, graph->node_count);
        
        if (current_node == -1) {
            break;
        }

        visited[current_node] = 1;

        // Check all neighbors
        for (int j = 0; j < graph->node_count; j++) {
            if (visited[j] != 1) {
                int new_distance = distances[current_node] + graph->adjacency_matrix[current_node][j];
                
                if (new_distance < distances[j]) {
                    distances[j] = new_distance;
                    
                    // Animate the path change
                    if (previous[j] != -1) {
                        // Remove old path
                        draw_edge(graph->nodes[previous[j]], graph->nodes[j], RED_EDGE_COLOR);
                        delay_milliseconds(EDGE_DELAY);
                        
                        // Draw new path
                        draw_edge(graph->nodes[current_node], graph->nodes[j], DESTINATION_EDGE_COLOR);
                        delay_milliseconds(EDGE_DELAY);
                    } else {
                        // Draw new path
                        delay_milliseconds(EDGE_DELAY);
                        draw_edge(graph->nodes[current_node], graph->nodes[j], DESTINATION_EDGE_COLOR);
                    }
                    
                    previous[j] = current_node;
                }
            }
        }
    }

    // Highlight the shortest path
    highlight_shortest_path(graph, previous);
}

void highlight_shortest_path(Graph* graph, int* previous) {
    int current = graph->destination.id;
    
    while (previous[current] != -1) {
        delay_milliseconds(PATH_DELAY);
        draw_path(graph->nodes[current], graph->nodes[previous[current]]);
        current = previous[current];
    }
} 