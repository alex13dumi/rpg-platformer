#include <Hero.hpp>

Hero::Hero(std::string name, uint8_t health, uint8_t speed, uint16_t attack, std::size_t row, std::size_t col, std::size_t width, std::size_t height):
_name(name), _health(health), _speed(speed), _attack(attack), _row(row), _col(col), _width(width), _height(height){}

Hero::~Hero(){

}
void Hero::upload_animation(){
    for (std::size_t i = 0; i < _row; i++) {
        for (std::size_t j = 0; j < _col; j++) {
            frame_rects.push_back(new SDL_Rect{ (int) (j*_width), (int) (i * _height), (int) _width, (int) _height });
        }
    }
    SDL_Log("Uploaded Hero animation");
}

void Hero::move(){

}