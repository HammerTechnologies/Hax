#!/bin/bash
cd `dirname $0`

echo "# Building (Emscripten) ..."
mkdir _CMAKE_EMSCRIPTEN
cd _CMAKE_EMSCRIPTEN
emcmake cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ..
emmake make NDEBUG=1
mv hax.js ../_build/hax.js
mv hax.wasm ../_build/hax.wasm
cd ..