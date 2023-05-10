#!/bin/bash
cd `dirname $0`

mkdir _build

echo "# Building (Desktop) ..."
mkdir _CMAKE
cd _CMAKE
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ..
make
mv hax ../_build/hax
cd ..

echo "# Building (Web) ..."
mkdir _CMAKE_EMSCRIPTEN
cd _CMAKE_EMSCRIPTEN
emcmake cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ..
emmake make NDEBUG=1
mv hax.js ../_build/hax.js
mv hax.wasm ../_build/hax.wasm
cd ..