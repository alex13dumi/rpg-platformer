cmake_minimum_required(VERSION 3.7)

project(SDL2Test)

find_package(SDL2 REQUIRED)
include_directories(include/ /usr/local/include/SDL2)
add_executable(SDL2Test src/test.cpp src/renderwindow.cpp src/system.cpp src/entity.cpp src/math.cpp src/sprites.cpp)
target_link_libraries(SDL2Test libSDL2.so /usr/local/lib/libSDL2_image.so)