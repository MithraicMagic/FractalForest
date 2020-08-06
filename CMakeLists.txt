cmake_minimum_required(VERSION 3.17)
project(fractaltree)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

add_definitions("-DGL_GLEXT_PROTOTYPES")

add_executable(fractaltree main.cpp environment_2d.cpp Foo.cpp Foo.h Vector3.cpp Vector3.h GLHelper.h Buffer.cpp Buffer.h)
target_link_libraries(fractaltree ftgl glut GLU GL)