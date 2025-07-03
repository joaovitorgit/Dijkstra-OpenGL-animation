#include "../include/renderer.h"
#include "../include/graph.h"
#include <GL/glut.h>
#include <string.h>
#include <stdio.h>

void init_gl() {
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
    glMatrixMode(GL_MODELVIEW);
    glClearColor(0.0, 0.0, 0.0, 1);
    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(5);
}

void reshape_window(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, width, height);
}

void clear_screen() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glFlush();
}

void draw_house(float cx, float cy) {
    // Main roof extension
    glBegin(GL_QUADS);
    glColor3f(0.9f, 0.5f, 0.2f);
    glVertex2d(cx+90, cy+40);    // top right
    glVertex2d(cx+120, cy+0);    // bottom right
    glVertex2d(cx+40, cy+0);     // bottom left
    glVertex2d(cx+25, cy+40);    // top left
    glEnd();

    // Main house body
    glBegin(GL_QUADS);
    glEnable(GL_LINE_SMOOTH);
    glColor3f(0.7f, 0.9f, 1.0f);
    glVertex2d(cx+110, cy+0);    // top right
    glVertex2d(cx+110, cy-20);   // bottom right
    glVertex2d(cx+40, cy-20);    // bottom left
    glVertex2d(cx+40, cy+0);     // top left
    glEnd();

    // House extension
    glBegin(GL_QUADS);
    glColor3f(0.6f, 0.8f, 0.9f);
    glVertex2d(cx+40, cy+0);     // top right
    glVertex2d(cx+40, cy-20);    // bottom right
    glVertex2d(cx+3, cy);        // bottom left
    glVertex2d(cx+3, cy+15);     // top left
    glEnd();

    // Roof triangle
    glBegin(GL_TRIANGLES);
    glColor3f(0.8f, 0.4f, 0.1f);
    glVertex2d(cx+25, cy+40);    // top
    glVertex2d(cx+40, cy+0);     // bottom right
    glVertex2d(cx-2, cy+17);     // bottom left
    glEnd();

    // Door
    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.2f, 0.2f);
    glVertex2d(cx+31, cy+0);     // top right
    glVertex2d(cx+31, cy-15);    // bottom right
    glVertex2d(cx+20, cy-10);    // bottom left
    glVertex2d(cx+20, cy+5);     // top left
    glEnd();

    // Window frame
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.5f, 0.5f);
    glVertex2d(cx+85, cy-2);     // top right
    glVertex2d(cx+85, cy-15);    // bottom right
    glVertex2d(cx+55, cy-15);    // bottom left
    glVertex2d(cx+55, cy-2);     // top left
    glEnd();

    // Window cross lines
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.3f, 0.3f);
    glVertex2i(cx+55, cy-9);     // horizontal line
    glVertex2i(cx+85, cy-9);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.0f, 0.3f, 0.3f);
    glVertex2i(cx+70, cy-2);     // vertical line
    glVertex2i(cx+70, cy-15);
    glEnd();

    glFlush();
}

void draw_node(float x, float y) {
    draw_house(x, y);
}

void set_edge_color(char color) {
    switch (color) {
        case NORMAL_EDGE_COLOR:
        case RED_EDGE_COLOR:
            glColor3f(0.3, 0.3, 0.3);  // Gray
            break;
        case DESTINATION_EDGE_COLOR:
            glColor3f(0.8, 0.8, 0.8);  // Light gray
            break;
        case PATH_EDGE_COLOR:
            glColor3f(0.4, 1.0, 0.1);  // Green
            break;
        default:
            glColor3f(0.3, 0.3, 0.3);  // Default gray
    }
}

void draw_edge(Node node1, Node node2, char color) {
    set_edge_color(color);
    
    // Draw the line between nodes
    glBegin(GL_LINES);
    glVertex2f(node1.x, node1.y);
    glVertex2f(node2.x, node2.y);
    glEnd();
    glFlush();

    // Calculate and display distance
    int mid_x, mid_y;
    get_midpoint(&mid_x, &mid_y, node1, node2);
    
    int distance = calculate_distance(node1, node2);
    char distance_string[10];
    sprintf(distance_string, "%d", distance);
    
    get_perpendicular_coordinates(&mid_x, &mid_y, node1, node2);
    draw_distance_label(distance_string, mid_x, mid_y);
    
    glFlush();
}

void draw_distance_label(char* text, int x, int y) {
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2i(x, y);
    int len = strlen(text);
    for (int i = 0; i < len; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }
    glFlush();
}

void draw_node_label(char label, int x, int y) {
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2i(x, y);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, label);
}

void draw_path(Node node1, Node node2) {
    draw_edge(node1, node2, PATH_EDGE_COLOR);
}

void get_midpoint(int* mid_x, int* mid_y, Node node1, Node node2) {
    *mid_x = (node1.x + node2.x) / 2;
    *mid_y = (node1.y + node2.y) / 2;
}

void get_perpendicular_coordinates(int* x, int* y, Node node1, Node node2) {
    int x1 = node1.x;
    int x2 = node2.x;
    int y1 = node1.y;
    int y2 = node2.y;

    float diff = (x2 - x1) ? (x2 - x1) : 0.0001;
    float slope = ((float)(y2 - y1)) / diff;
    float perpendicular_slope = -1 * (1 / slope);

    *x = *x + 25;
    *y = *y + perpendicular_slope * (*x) + 7;
} 