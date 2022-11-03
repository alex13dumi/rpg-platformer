#ifndef SDL2TEST_HERO_HPP
#define SDL2TEST_HERO_HPP
#include <SDL.h>
#include <vector>
#include <string>
#include <RenderWindow.hpp>
#define Vector std::vector<std::pair<std::size_t, std::size_t>>

class Hero
{
public:
    Hero(std::string name, uint8_t health, uint8_t speed, uint16_t attack, std::size_t _row, std::size_t _col, std::size_t _width, std::size_t _height);
    ~Hero();
    void upload_animation();
    void handleEvent(SDL_Event &event);
    void move();
    void render(RenderWindow window, SDL_Rect* src, SDL_Rect* dst);

    std::size_t _row,_col,_width,_height;
    std::vector<SDL_Rect*> frame_rects;
    Vector _current_hero_animation;
    Vector idle1  {{0, 0}, {0, 1}, {0, 2}, {0, 3}};
    Vector crouch {{0, 4}, {0, 5}, {0, 6}, {1, 0}};
    Vector run    {{1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6}};
    Vector jump   {{2, 0}, {2, 1}, {2, 2}, {2, 3}};
    Vector mid    {{2, 4}, {2, 5}, {2, 6}, {3, 0}};
    Vector fall   {{3, 1}, {3, 2}};
    Vector slide  {{3, 3}, {3, 4}, {3, 5}, {3, 6}, {4, 0}};
    Vector grab   {{4, 1}, {4, 2}, {4, 3}, {4, 4}};
    Vector climb  {{4, 5}, {4, 6}, {5, 0}, {5, 1}, {5, 2}};
    Vector idle2  {{5, 3}, {5, 4}, {5, 5}, {5, 6}};
    Vector attack1{{6, 0}, {6, 1}, {6, 2}, {6, 3}, {6, 4}};
    Vector attack2{{6, 5}, {6, 6}, {7, 0}, {7, 1}, {7, 2}, {7, 3}};
    Vector attack3{{7, 4}, {7, 5}, {7, 6}, {8, 0}, {8, 1}, {8, 2}};
    Vector hurt   {{8, 3}, {8, 4}, {8, 5}};
    Vector die    {{8, 6}, {9, 0}, {9, 1}, {9, 2}, {9, 3}, {9, 4}, {9, 5}};
    Vector jump2  {{9, 6}, {10, 0}, {10, 1}};

private:
    std::string _name;
    uint8_t _health;
    uint8_t _speed;
    uint16_t _attack;
    uint8_t posX;
    uint8_t posY;
    uint8_t velX;
    uint8_t velY;
    static const int VEL = 10;
};
#endif //SDL2TEST_HERO_HPP
