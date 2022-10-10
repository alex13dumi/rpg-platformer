#ifndef SDL2TEST_ENTITY_HPP
#define SDL2TEST_ENTITY_HPP
#include <SDL.h>
#include <SDL_image.h>
#include <Math.hpp>

class Entity{
public:
    Entity(Vector2f pos, SDL_Texture* texture);
    ~Entity() = default;
    Vector2f& getPos();
    SDL_Texture* getText();
    SDL_Rect getCurrentFrame();

private:
    Vector2f _pos;
    SDL_Rect _currentFrame;
    SDL_Texture* _texture;
};
#endif //SDL2TEST_ENTITY_HPP
