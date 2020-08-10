cmake_minimum_required(VERSION 3.17)
project(fractalforest)

include_directories("/usr/include/freetype2")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

add_definitions("-DGL_GLEXT_PROTOTYPES")

add_executable(fractalforest Main.cpp Environment.cpp Graphics.cpp Graphics.h Vector3.cpp Vector3.h GLHelper.h GLBuffer.cpp GLBuffer.h Transformer.cpp Transformer.h Forest.cpp Forest.h)
target_link_libraries(fractalforest ftgl glut GLU GL)