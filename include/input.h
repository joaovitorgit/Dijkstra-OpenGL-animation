#ifndef INPUT_H
#define INPUT_H

#include "graph.h"

// Function declarations for input handling
void handle_mouse_click(int button, int state, int x, int y);
void handle_keyboard_input(unsigned char key, int x, int y);
void process_left_click(Graph* graph, int x, int y);
void process_right_click(Graph* graph, int x, int y);
void display_instructions();

// Global variables for input handling
extern int show_instructions;
extern int algorithm_running;

#endif // INPUT_H 