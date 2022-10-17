#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <Entity.hpp>
#include <vector>

class RenderWindow 
{
public:
	RenderWindow(const char* p_title, int p_w, int p_h);
    ~RenderWindow() = default;
    SDL_Texture* loadTexture(const char* p_filePath);
    void cleanUp();
    void clear();
    void render(Entity& p_entity);
    void display();
    SDL_Window* getWindow();
    SDL_Renderer* getRenderer();
private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;
};
