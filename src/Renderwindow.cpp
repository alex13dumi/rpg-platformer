#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <RenderWindow.hpp>
#include <System.hpp>

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
        :_window(NULL), _renderer(NULL)
{
    /*Initialize SDL*/
    System CPU;
    SDL_Log("Platform: %s, RAM: %d MB", CPU.getPlatform(), CPU.getRam());

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("SDL_Init has failed. SDL_Error: %s", SDL_GetError());
    }
    else if (!(IMG_Init(IMG_INIT_PNG))){
        SDL_Log("IMG_init has failed. SDL_Error: %s", SDL_GetError());
    }
    SDL_Log("Succesfully initialised ! Let's play the game !");

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
    SDL_Texture* backgroundTexture = loadTexture("../res/gfx/background.png");
    if (backgroundTexture == NULL){
        SDL_Log("Couldn't load background !");
        return false;
    }
    _textures.emplace_back(grassTexture);
    _textures.emplace_back(heroTexture);
    _textures.emplace_back(backgroundTexture);
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

void RenderWindow::render(SDL_Texture* texture, SDL_Rect* src, SDL_Rect* dst)
{
    SDL_RenderCopy(_renderer, texture, src, dst );
}

void RenderWindow::refresh()
{
    SDL_RenderPresent(_renderer);

}

SDL_Window* RenderWindow::getWindow() { return _window; }
SDL_Renderer* RenderWindow::getRenderer(){ return _renderer; }
std::vector<SDL_Texture*> RenderWindow::getTextures(){ return _textures; }
