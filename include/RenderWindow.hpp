#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

class RenderWindow 
{
public:
	RenderWindow(const char* p_title, int p_w, int p_h);
    ~RenderWindow() = default;
    bool loadTextures();
    SDL_Texture* loadTexture(const char* path);
    void cleanUp();
    void clear();
    void refresh();
    SDL_Window* getWindow();
    SDL_Renderer* getRenderer();
    std::vector<SDL_Texture*> getTextures();

private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;
    std::vector<SDL_Texture*> _textures;
};
