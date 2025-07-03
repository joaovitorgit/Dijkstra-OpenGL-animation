#ifndef RENDERER_H
#define RENDERER_H

#include "graph.h"

// Function declarations for rendering
void init_gl();
void reshape_window(int width, int height);
void clear_screen();
void draw_node(float x, float y);
void draw_edge(Node node1, Node node2, char color);
void draw_distance_label(char* text, int x, int y);
void draw_node_label(char label, int x, int y);
void draw_path(Node node1, Node node2);
void get_perpendicular_coordinates(int* x, int* y, Node node1, Node node2);
void get_midpoint(int* mid_x, int* mid_y, Node node1, Node node2);
void set_edge_color(char color);
void draw_house(float cx, float cy);

#endif // RENDERER_H 