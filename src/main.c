#include "../include/constants.h"
#include "../include/graph.h"
#include "../include/renderer.h"
#include "../include/input.h"
#include "../include/dijkstra.h"
#include <GL/glut.h>
#include <stdio.h>

// Global variables
Graph global_graph;
int window_height = WINDOW_HEIGHT;

void display() {
    clear_screen();
    display_instructions();
}

void reshape(int width, int height) {
    window_height = height;
    reshape_window(width, height);
}

int main(int argc, char** argv) {
    // Initialize graph
    init_graph(&global_graph);

    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Dijkstra's Algorithm Visualization");

    // Initialize OpenGL
    init_gl();

    // Set up callbacks
    glutReshapeFunc(reshape);
    glutMouseFunc(handle_mouse_click);
    glutKeyboardFunc(handle_keyboard_input);
    glutDisplayFunc(display);

    // Display initial instructions
    display_instructions();

    // Start main loop
    glutMainLoop();

    return 0;
} 