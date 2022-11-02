#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <RenderWindow.hpp>
#include <Entity.hpp>

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
        :_window(NULL), _renderer(NULL)
{
    Uint32 flags = SDL_WINDOW_FULLSCREEN | SDL_WINDOW_RESIZABLE | SDL_INIT_VIDEO;
    _window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, flags);

    if (_window == NULL){
        std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
    }

    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
}

bool RenderWindow::loadTextures(){
    SDL_Texture* grassTexture = loadTexture("../res/gfx/grass.png");
    if (grassTexture == NULL){
        SDL_Log("Couldn't load grass texture !");
        return false;
    }
    SDL_Texture* heroTexture = loadTexture("../res/gfx/adventurer-sheet.png");
    if (heroTexture == NULL){
        SDL_Log("Couldn't load main hero texture !");
        return false;
    }
    _textures.emplace_back(grassTexture);
    _textures.emplace_back(heroTexture);
    return true;
}

SDL_Texture* RenderWindow::loadTexture(const char* path){
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(_renderer, path);

    if (texture == NULL)
        SDL_Log("Failed to load texture. Error: %s", SDL_GetError());

    return texture;
}

void RenderWindow::cleanUp()
{
    SDL_DestroyWindow(_window);
}

void RenderWindow::clear()
{
    SDL_RenderClear(_renderer);
}

void RenderWindow::render(Entity& p_entity)
{
    SDL_Rect src;
    src.x = p_entity.getCurrentFrame().x;
    src.y = p_entity.getCurrentFrame().y;
    src.w = p_entity.getCurrentFrame().w;
    src.h = p_entity.getCurrentFrame().h;

    SDL_Rect dst;
    dst.x = p_entity.getPos()._x * 4;
    dst.y = p_entity.getPos()._y * 4;
    dst.w = p_entity.getCurrentFrame().w * p_entity.getResize()._x;
    dst.h = p_entity.getCurrentFrame().h * p_entity.getResize()._y;
    SDL_RenderCopy(_renderer, p_entity.getText(), &src, &dst);
}

void RenderWindow::refresh()
{
    SDL_RenderPresent(_renderer);

}

SDL_Window* RenderWindow::getWindow() { return _window; }
SDL_Renderer* RenderWindow::getRenderer(){ return _renderer; }
std::vector<SDL_Texture*> RenderWindow::getTextures(){ return _textures; }
