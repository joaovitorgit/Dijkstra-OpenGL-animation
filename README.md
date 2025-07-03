# Dijkstra's Algorithm OpenGL Animation

A 2D visualization of Dijkstra's shortest path algorithm implemented in C using OpenGL. This project creates an interactive graph where users can place nodes (represented as houses) and edges, then watch Dijkstra's algorithm find the shortest path between two selected nodes in real-time.

## Features

- **Interactive Graph Creation**: Click to place nodes (houses) and create edges between them
- **Real-time Animation**: Watch Dijkstra's algorithm execute step-by-step with visual feedback
- **Distance Calculation**: Automatic distance calculation between connected nodes
- **Visual Path Highlighting**: The shortest path is highlighted in red during execution
- **House-themed Nodes**: Nodes are represented as colorful houses for better visualization
- **Maximum 26 Nodes**: Support for up to 26 nodes (A-Z labeling)

## Prerequisites

Before running this project, make sure you have the following installed:

- **GCC/G++ Compiler**
- **OpenGL Development Libraries**
- **GLUT (OpenGL Utility Toolkit)**
- **GLEW (OpenGL Extension Wrangler Library)**

### Installation on Ubuntu/Debian:
```bash
sudo apt-get update
sudo apt-get install build-essential
sudo apt-get install freeglut3-dev libgl1-mesa-dev libglu1-mesa-dev libglew-dev
```

### Installation on macOS:
```bash
brew install freeglut glew
```

### Installation on CentOS/RHEL:
```bash
sudo yum groupinstall "Development Tools"
sudo yum install freeglut-devel mesa-libGL-devel mesa-libGLU-devel glew-devel
```

## Compilation and Execution

### Using Makefile (Recommended):
```bash
make
./dijkstra
```

### Manual Compilation:
```bash
g++ dijkstra.c -o dijkstra -lglut -lGL -lGLU -lGLEW
./dijkstra
```

## How to Use

### Creating the Graph:
1. **Add Nodes**: Click anywhere in the window to place a house (node)
2. **Create Edges**: Click on an existing node, then click on another node to create an edge between them
3. **Set Source**: Press 'S' and click on a node to set it as the starting point
4. **Set Destination**: Press 'D' and click on a node to set it as the destination

### Running Dijkstra's Algorithm:
- Press 'R' to start the algorithm animation
- Watch as the algorithm explores nodes and finds the shortest path
- The shortest path will be highlighted in red

### Controls:
- **Mouse Click**: Place nodes or select nodes for edges
- **'S' Key**: Set source node (starting point)
- **'D' Key**: Set destination node (end point)
- **'R' Key**: Run Dijkstra's algorithm
- **'C' Key**: Clear the graph and start over
- **'Q' Key**: Quit the application

## Algorithm Visualization

The animation shows:
- **Gray Edges**: Regular connections between nodes
- **Red Edges**: Current shortest path being explored
- **Distance Labels**: Euclidean distance between connected nodes
- **Step-by-step Execution**: Visual feedback of the algorithm's progress

## Technical Details

- **Language**: C with OpenGL
- **Maximum Nodes**: 26 (labeled A-Z)
- **Window Size**: 1080x1020 pixels
- **Node Representation**: Houses with roofs, doors, and windows
- **Distance Calculation**: Euclidean distance between node centers

## Project Structure

```
Dijkstra-OpenGL-animation/
├── dijkstra.c          # Main source code
├── Makefile           # Build configuration
├── README.md          # This file
└── Trabalho Prático 2.pdf  # Original assignment (Portuguese)
```

## License

This project was created as part of a practical assignment for a computer graphics course.

## Screenshot

![Dijkstra Animation](https://user-images.githubusercontent.com/77855082/145925267-2ba57df6-b5bc-4247-8146-b7f6345337e2.gif)

*The animation shows the step-by-step execution of Dijkstra's algorithm finding the shortest path between two nodes in a graph.*
