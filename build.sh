#!/bin/bash
set -euo pipefail     # abort on fail

cd `dirname $0`

echo "# Creating folders for CMake ..."
mkdir -p _CMAKE/_GLFW
mkdir -p _CMAKE/_DESKTOP

echo "# Building GLFW3 ..."
cd lib/glfw-3.3.8
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=OFF -DGLFW_BUILD_DOCS=OFF -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_INSTALL=OFF -B ../../_CMAKE/_GLFW
cd ../../_CMAKE/_GLFW
make
cd ../..

echo "# Building (Desktop) ..."
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -B _CMAKE/_DESKTOP
cd _CMAKE/_DESKTOP
make
mv hax ../../_build/hax
cd ../..
