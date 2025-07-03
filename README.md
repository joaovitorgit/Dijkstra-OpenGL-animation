# Dijkstra's Algorithm OpenGL Animation

A 2D visualization of Dijkstra's shortest path algorithm implemented in C using OpenGL. This project creates an interactive graph where users can place nodes (represented as houses) and edges, then watch Dijkstra's algorithm find the shortest path between two selected nodes in real-time.

## Features

- **Interactive Graph Creation**: Click to place nodes (houses) and create edges between them
- **Real-time Animation**: Watch Dijkstra's algorithm execute step-by-step with visual feedback
- **Distance Calculation**: Automatic distance calculation between connected nodes
- **Visual Path Highlighting**: The shortest path is highlighted in green during execution
- **House-themed Nodes**: Nodes are represented as colorful houses for better visualization
- **Maximum 26 Nodes**: Support for up to 26 nodes (A-Z labeling)
- **Modular Architecture**: Clean, well-structured code with separation of concerns

## Project Structure

```
Dijkstra-OpenGL-animation/
├── include/                 # Header files
│   ├── constants.h         # Global constants and definitions
│   ├── graph.h            # Graph data structures and operations
│   ├── renderer.h         # OpenGL rendering functions
│   ├── dijkstra.h         # Algorithm implementation
│   └── input.h            # User input handling
├── src/                   # Source files
│   ├── main.c            # Main application entry point
│   ├── graph.c           # Graph operations implementation
│   ├── renderer.c        # Rendering implementation
│   ├── dijkstra.c        # Algorithm implementation
│   └── input.c           # Input handling implementation
├── Makefile              # Build configuration
├── README.md             # This file
└── Trabalho Prático 2.pdf  # Original assignment (Portuguese)
```

## Prerequisites

Before running this project, make sure you have the following installed:

- **GCC Compiler**
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
gcc -Wall -Wextra -std=c99 -Iinclude src/*.c -o dijkstra -lglut -lGL -lGLU -lGLEW
./dijkstra
```

### Build Options:
- `make clean` - Remove build artifacts
- `make install-deps` - Install dependencies (Ubuntu/Debian)
- `make install-deps-mac` - Install dependencies (macOS)
- `make install-deps-centos` - Install dependencies (CentOS/RHEL)

## How to Use

### Creating the Graph:
1. **Add Nodes**: Click anywhere in the window to place a house (node)
2. **Create Edges**: Click on an existing node, then click on another node to create an edge between them
3. **Set Source**: Right-click on a node to set it as the starting point
4. **Set Destination**: Right-click on another node to set it as the destination

### Running Dijkstra's Algorithm:
- Press **Enter** to start the algorithm animation
- Watch as the algorithm explores nodes and finds the shortest path
- The shortest path will be highlighted in green

### Controls:
- **Left Mouse Click**: Place nodes or select nodes for edges
- **Right Mouse Click**: Set source/destination nodes
- **Enter Key**: Run Dijkstra's algorithm
- **C Key**: Clear the graph and start over
- **Q Key**: Quit the application

## Algorithm Visualization

The animation shows:
- **Gray Edges**: Regular connections between nodes
- **Light Gray Edges**: Current path being explored
- **Green Edges**: Final shortest path
- **Distance Labels**: Euclidean distance between connected nodes
- **Step-by-step Execution**: Visual feedback of the algorithm's progress

## Technical Details

- **Language**: C99 with OpenGL
- **Architecture**: Modular design with separate concerns
- **Maximum Nodes**: 26 (labeled A-Z)
- **Window Size**: 1080x1020 pixels
- **Node Representation**: Houses with roofs, doors, and windows
- **Distance Calculation**: Euclidean distance between node centers
- **Animation Delays**: Configurable timing for visual effects

## Code Organization

The project follows a clean modular architecture:

- **Graph Module**: Handles graph data structures and operations
- **Renderer Module**: Manages all OpenGL rendering and visualization
- **Dijkstra Module**: Implements the shortest path algorithm
- **Input Module**: Processes user interactions and events
- **Constants**: Centralized configuration and definitions

## License

This project was created as part of a practical assignment for a computer graphics course.

## Screenshot

![Dijkstra Animation](https://user-images.githubusercontent.com/77855082/145925267-2ba57df6-b5bc-4247-8146-b7f6345337e2.gif)

*The animation shows the step-by-step execution of Dijkstra's algorithm finding the shortest path between two nodes in a graph.*
