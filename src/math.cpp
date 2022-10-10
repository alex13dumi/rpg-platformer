#include <SDL.h>
#include <Math.hpp>

Vector2f::Vector2f(): _x(0.0), _y(0.0){ }
Vector2f::Vector2f(float x , float y): _x(x), _y(y){ }
void Vector2f::print() { SDL_Log("x = %.2f , y = %.2f", _x, _y ); }
