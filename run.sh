#!/bin/bash

echo "Compiling C files..."
gcc main.c dijkstra.c Heaps.c graph.c simulation.c -o Combined

if [ $? -eq 0 ]; then
    echo "Compilation successful. Running program..."
    ./Combined

    echo "Launching Python UI..."
    python3 ui.py
else
    echo "Compilation failed!"
fi
