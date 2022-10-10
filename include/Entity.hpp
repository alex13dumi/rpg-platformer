#ifndef SDL2TEST_ENTITY_HPP
#define SDL2TEST_ENTITY_HPP
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <Math.hpp>

class Entity{
public:
    Entity(Vector2f pos, SDL_Texture* texture, Vector2f size);
    ~Entity() = default;
    Vector2f& getPos();
    SDL_Texture* getText();
    SDL_Rect getCurrentFrame();
    Vector2f& getResize();

private:
    Vector2f _resize;
    Vector2f _pos;
    SDL_Texture* _texture;
    SDL_Rect _currentFrame;
};
#endif //SDL2TEST_ENTITY_HPP
