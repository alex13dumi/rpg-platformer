cmake_minimum_required(VERSION 3.7)

project(SDL2Test)

find_package(SDL2 REQUIRED)
include_directories(include/ /usr/local/include/SDL2 )
add_executable(SDL2Test src/Main.cpp src/Renderwindow.cpp src/System.cpp src/Math.cpp src/Hero.cpp)
target_link_libraries(SDL2Test SDL2main SDL2 SDL2_image)