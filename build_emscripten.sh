#!/bin/bash
cd `dirname $0`

echo "# Creating folders for CMake ..."
mkdir _CMAKE
mkdir _CMAKE/_EMSCRIPTEN

echo "# Building (Emscripten) ..."
emcmake cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -B _CMAKE/_EMSCRIPTEN
cd _CMAKE/_EMSCRIPTEN
emmake make NDEBUG=1
if [ $? -ne 0 ]; then
  exit 1
fi
mv hax.js ../../_build/hax.js
mv hax.wasm ../../_build/hax.wasm
mv hax.data ../../_build/hax.data
cd ../..
