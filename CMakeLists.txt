#Minimum version
cmake_minimum_required(VERSION 2.9)

#Define project
project(hax)

#Define file groups
file(GLOB HAX_FILES "src/*.cpp")

#Add header and lib directories
include_directories(${INCLUDE_DIRECTORIES} ${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw-3.3.8/include)
link_directories(${LINK_DIRECTORIES} ${CMAKE_CURRENT_SOURCE_DIR}/_CMAKE/_GLFW/src)

#Add executable targets
add_executable(hax ${HAX_FILES})

#Add platform specific options
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -fno-exceptions -fno-rtti -Wall -Wextra -Wpedantic -Werror")
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	message("Platform is macOS")
	add_definitions(-DGL_SILENCE_DEPRECATION)
	target_link_libraries(hax glfw3 "-framework AppKit" "-framework CoreVideo" "-framework IOKit" "-framework OpenGL" ${TARGET_LINK_LIBRARIES})
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	message("Platform is Linux")
	target_link_libraries(hax glfw3 GL X11 Xrandr Xi Xxf86vm Xinerama Xcursor pthread dl fontconfig freetype ${TARGET_LINK_LIBRARIES})
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
	message("Platform is Emscripten")
	add_definitions(-DNO_SKIA)
	set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-o hax.js -s USE_GLFW=3 -s ALLOW_MEMORY_GROWTH=1 -s NO_EXIT_RUNTIME=1")
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
      message("Platform is Windows")
      target_link_libraries(hax glfw3 ${TARGET_LINK_LIBRARIES})
else (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	message("Unrecognized platform " ${CMAKE_SYSTEM_NAME})
endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")