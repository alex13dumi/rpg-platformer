#include <Entity.hpp>

Entity::Entity(Vector2f pos, SDL_Texture* texture): _pos(pos), _texture(texture) {
    _currentFrame.x = 0;
    _currentFrame.y = 0;
    _currentFrame.w = 32;
    _currentFrame.h = 32;
}

SDL_Texture* Entity::getText() { return _texture; };
SDL_Rect Entity::getCurrentFrame() { return _currentFrame; }
Vector2f& Entity::getPos() { return _pos; }
