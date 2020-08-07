cmake_minimum_required(VERSION 3.17)
project(fractalforest)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

add_definitions("-DGL_GLEXT_PROTOTYPES")

add_executable(fractalforest Main.cpp Environment.cpp Foo.cpp Foo.h Vector3.cpp Vector3.h GLHelper.h GLBuffer.cpp GLBuffer.h Transformer.cpp Transformer.h)
target_link_libraries(fractalforest ftgl glut GLU GL)