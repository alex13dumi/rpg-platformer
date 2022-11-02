#include <Sprites.hpp>

Hero::Hero(std::size_t row, std::size_t col, std::size_t widht, std::size_t height): _col(col), _row(row), _width(widht), _height(height){ };
void Hero::addRects() {
    for (std::size_t i = 0; i < _row; i++) {
        for (std::size_t j = 0; j < _col; j++) {
            rects.push_back(new SDL_Rect{ (int) (j*_width), (int) (i * _height), (int) _width, (int) _height });
        }
    }
}
