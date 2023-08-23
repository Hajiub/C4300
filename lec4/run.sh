#!/bin/bash

# Script to compile and run a C/C++ program
# Usage: ./compile_and_run.sh <source_file>

# Check for the correct number of arguments
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <source_file>"
    exit 1
fi

# Extract the filename without extension
filename=$(basename "$1")
filename_without_extension="${filename%.*}"

# Create a directory for the compiled binary
if [ ! -d "bin" ]; then 
	mkdir -p "bin"
fi

# Compile the source code
echo "Compiling $1..."
g++ "$1" -o "bin/$filename_without_extension"  -lsfml-graphics -lsfml-window -lsfml-system

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful."

    # Run the compiled binary
    echo "Running $filename_without_extension..."
    "./bin/$filename_without_extension"

    # Clean up the binary
    rm -f "bin/$filename_without_extension"
else
    echo "Compilation failed."
fi
