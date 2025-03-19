#!/bin/bash

# Check if the -r parameter is given
if [ "$1" == "-r" ]; then
    cd build
    make
    cp arcade ..
    exit 0
fi

# Remove the build folder if it exists
if [ -d "build" ]; then
    rm -rf build
fi

# Create and navigate to the build directory
mkdir build

# move to build
cd build

# create file
cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_RUNTIME_OUTPUT_DIRECTORY=./

# Build the project
cmake --build .

# Move the nts file to the parent directory
mv arcade ..

# Navigate back to the parent directory
cd ..