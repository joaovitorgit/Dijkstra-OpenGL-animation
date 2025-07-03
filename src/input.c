#include "../include/input.h"
#include "../include/renderer.h"
#include "../include/dijkstra.h"
#include <GL/glut.h>
#include <stdio.h>
#include <string.h>

// Global variables for input handling
int show_instructions = 1;
int algorithm_running = 0;
extern Graph global_graph;
extern int window_height;

void display_instructions() {
    if (show_instructions) {
        glColor3f(1.0, 0.0, 0.0);
        glRasterPos2i(10, window_height - 30);
        char* instruction = "Click to place nodes, right-click to set source/destination, press Enter to run Dijkstra";
        int len = strlen(instruction);
        for (int i = 0; i < len; i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, instruction[i]);
        }
        glFlush();
    }
}

void handle_mouse_click(int button, int state, int x, int y) {
    if (algorithm_running) {
        return;
    }

    // Clear instructions on first interaction
    if (show_instructions) {
        show_instructions = 0;
        clear_screen();
    }

    // Adjust coordinate system
    y = window_height - y;

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        process_left_click(&global_graph, x, y);
    } else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        process_right_click(&global_graph, x, y);
    }
}

void process_left_click(Graph* graph, int x, int y) {
    if (!is_node_at_position(graph, x, y)) {
        // Create new node
        if (graph->node_count >= MAX_VERTICES) {
            return;
        }

        draw_node(x, y);
        add_node(graph, x, y);
        
        // Draw node label
        char label = 'A' + graph->node_count - 1;
        draw_node_label(label, x - 5, y - 14);
        
    } else {
        // Select existing node for edge creation
        Node* selected_node = get_node_at_position(graph, x, y);
        if (selected_node) {
            static Node* first_node = NULL;
            
            if (first_node == NULL) {
                first_node = selected_node;
            } else if (first_node != selected_node) {
                // Create edge between two selected nodes
                add_edge(graph, first_node, selected_node);
                draw_edge(*first_node, *selected_node, NORMAL_EDGE_COLOR);
                
                // Redraw node labels
                char label1 = 'A' + first_node->id;
                char label2 = 'A' + selected_node->id;
                draw_node_label(label1, first_node->x - 5, first_node->y - 14);
                draw_node_label(label2, selected_node->x - 5, selected_node->y - 14);
                
                first_node = NULL;
            }
        }
    }
}

void process_right_click(Graph* graph, int x, int y) {
    if (graph->node_count == 0) {
        return;
    }

    Node* clicked_node = get_node_at_position(graph, x, y);
    if (clicked_node) {
        if (!graph->source_defined) {
            set_source(graph, clicked_node);
            printf("Source node set to %c\n", 'A' + clicked_node->id);
        } else if (!graph->destination_defined && clicked_node->id != graph->source.id) {
            set_destination(graph, clicked_node);
            printf("Destination node set to %c\n", 'A' + clicked_node->id);
        }
    }
}

void handle_keyboard_input(unsigned char key, int x, int y) {
    if (!is_valid_graph_for_dijkstra(&global_graph)) {
        printf("Source and destination nodes must be defined\n");
        return;
    }

    if (key == 13) { // Enter key
        algorithm_running = 1;
        run_dijkstra(&global_graph);
        algorithm_running = 0;
    } else if (key == 'q' || key == 'Q') {
        exit(0);
    } else if (key == 'c' || key == 'C') {
        // Clear graph
        init_graph(&global_graph);
        clear_screen();
        show_instructions = 1;
        display_instructions();
    }
} 