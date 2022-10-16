#include <Entity.hpp>
#include <Math.hpp>

Entity::Entity(Vector2f pos, SDL_Texture* texture, Vector2f resize): _pos(pos), _texture(texture), _resize(resize) {
    _currentFrame.x = 0;
    _currentFrame.y = 0;
    _currentFrame.w = 32;
    _currentFrame.h = 32;
}

Vector2f& Entity::getPos() { return _pos; }
SDL_Texture* Entity::getText() { return _texture; }
SDL_Rect Entity::getCurrentFrame() { return _currentFrame; }
Vector2f& Entity::getResize(){ return _resize; }
