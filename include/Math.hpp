#pragma once
#ifndef SDL2TEST_MATH_HPP
#define SDL2TEST_MATH_HPP
#include <vector>

struct Vector2f{
    Vector2f();
    Vector2f(float x, float y);
    void print();

    float _x;
    float _y;
};
#endif //SDL2TEST_MATH_HPP
