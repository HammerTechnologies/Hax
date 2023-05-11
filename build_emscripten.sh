#!/bin/bash
cd `dirname $0`

echo "# Creating folders for CMake ..."
mkdir _CMAKE
mkdir _CMAKE/_EMSCRIPTEN

echo "# Building (Emscripten) ..."
emcmake cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -B _CMAKE/_EMSCRIPTEN
cd _CMAKE/_EMSCRIPTEN
emmake make NDEBUG=1
mv hax.js ../../_build/hax.js
mv hax.wasm ../../_build/hax.wasm
cd ../..
