cmake_minimum_required(VERSION 2.9)
project(hax)
file(GLOB HAX_FILES "src/*.cpp" "src/*/*.cpp" "src/*/*/*.cpp" "lib/glad_gles20/src/glad.c")
add_definitions(-DSTBI_ONLY_PNG)
include_directories(
	${INCLUDE_DIRECTORIES}
	${CMAKE_CURRENT_SOURCE_DIR}/lib/glad_gles20/include
	${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw-3.3.8/include
	${CMAKE_CURRENT_SOURCE_DIR}/lib/stb)
link_directories(
	${LINK_DIRECTORIES}
	${CMAKE_CURRENT_SOURCE_DIR}/_CMAKE/_GLFW/src)
add_executable(hax ${HAX_FILES})

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -fno-exceptions -fno-rtti -Wall -Wextra -Wpedantic -Werror -Wno-unused-function")
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	message("Platform is macOS")
	add_definitions(-DGL_SILENCE_DEPRECATION)
	target_link_libraries(hax glfw3 "-framework AppKit" "-framework CoreVideo" "-framework IOKit" "-framework OpenGL" ${TARGET_LINK_LIBRARIES})
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	message("Platform is Linux")
	target_link_libraries(hax glfw3 GL X11 Xrandr Xi Xxf86vm Xinerama Xcursor pthread dl ${TARGET_LINK_LIBRARIES})
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
	message("Platform is Emscripten")
	add_definitions(-DNO_SKIA)
	set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-o hax.js --preload-file ../../_build/assets@/assets -s USE_GLFW=3 -s ALLOW_MEMORY_GROWTH=1 -s NO_EXIT_RUNTIME=1")
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	message("Platform is Windows")
	target_link_libraries(hax glfw3 ${TARGET_LINK_LIBRARIES})
else (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	message("Unrecognized platform " ${CMAKE_SYSTEM_NAME})
endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
