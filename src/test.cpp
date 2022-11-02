#include <iostream>
#include <vector>
#include <chrono>
#include <cassert>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_surface.h>
#include <RenderWindow.hpp>
#include <Entity.hpp>
#include <System.hpp>
#include <Sprites.hpp>

#define WIDTH 1280
#define HEIGHT 720
/*#define assertm(exp, msg) assert(((void)msg, exp))*/
#define assertm(exp, msg) assert((msg, exp))

typedef std::chrono::high_resolution_clock Clock;

int main(int argc, char* args[]) {
    /*Initialize SDL*/
    System CPU;
    SDL_Log("Platform: %s, RAM: %d MB", CPU.getPlatform(), CPU.getRam());

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "HEY.. SDL_Init HAS FAILED. SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    else if (!(IMG_Init(IMG_INIT_PNG))){
        std::cout << "IMG_init has failed. SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    SDL_Log("Succesfully initialised ! Let's play the game !");
    /*Creates a window*/
    RenderWindow window("GAME v1.0", WIDTH, HEIGHT);
    /*Load textures*/
    assertm(window.loadTextures(), "Couldn't load textures");

    std::vector<Entity> entitiees = {Entity( Vector2f(0, 120), window.getTextures()[0], Vector2f(8,8)),
                                     Entity( Vector2f(64, 120), window.getTextures()[0], Vector2f(8,8)),
                                     Entity( Vector2f(128, 120), window.getTextures()[0], Vector2f(8,8)),
                                     Entity( Vector2f(192, 120), window.getTextures()[0], Vector2f(8,8)),
                                     Entity( Vector2f(256, 120), window.getTextures()[0], Vector2f(8,8))};

    /* Each sprite is an 50 x 37 images. TO DO: Store them in a JSON LUA data file*/
    Hero hero(11, 7, 50, 37);
    /*Allocate memory for animations that are gonna be added for the hero*/
    hero.addRects();
    /*Select current_hero_animation animation for the hero*/
    Vector current_hero_animation = hero.idle1;
    size_t index = 0;

    double maxDuration = 150;
    double timeBuffer = 0;
    double timeElapsed = 0;
    bool gameRunning = true;
    SDL_Event event;

    while (gameRunning)
    {
        double elapsedNano = 0;
        auto t1 = Clock::now();
        while (SDL_PollEvent(&event)) {
            if(event.window.type == SDL_WINDOWEVENT ){
                switch (event.window.event) {
                    case SDL_WINDOWEVENT_SHOWN:
                    {
                        SDL_Log("Window %d has been shown", event.window.windowID);
                    }
                }
            }
            else if (event.key.keysym.sym == SDLK_ESCAPE | event.type == SDL_QUIT ) {
                gameRunning = false;
                SDL_Log("Closing game...");
                SDL_Quit();
            }
            /* Each time a key is pressed a new animation sequence starts.*/
            else if (event.type == SDL_KEYDOWN) {
                SDL_Log("User pressed down a key");
                if (event.key.keysym.scancode == SDL_SCANCODE_Q) {
                    current_hero_animation = hero.idle1;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_W) {
                    current_hero_animation = hero.crouch;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_D) {
                    current_hero_animation = hero.run;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_R) {
                    current_hero_animation = hero.jump;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_T) {
                    current_hero_animation = hero.mid;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_Y) {
                    current_hero_animation = hero.fall;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_U) {
                    current_hero_animation = hero.slide;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_I) {
                    current_hero_animation = hero.grab;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_O) {
                    current_hero_animation = hero.climb;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_P) {
                    current_hero_animation = hero.idle2;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_A) {
                    current_hero_animation = hero.attack1;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_S) {
                    current_hero_animation = hero.attack2;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_E) {
                    current_hero_animation = hero.attack3;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_F) {
                    current_hero_animation = hero.hurt;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_G) {
                    current_hero_animation = hero.die;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_H) {
                    current_hero_animation = hero.jump;
                }
                index = 0;
            }
        }

        window.clear();
        /*After the event loop we can start the rendering*/
        for(auto e:entitiees)
            window.render(e);

        std::pair<size_t, size_t> current_hero_animationPair = current_hero_animation[index];
        size_t position = current_hero_animationPair.second + current_hero_animationPair.first * hero._col;
        SDL_Rect* dstrect;
        SDL_Rect dst = {256, 394, 120, 120};
        dstrect = &dst;
        SDL_RenderCopy(window.getRenderer(), window.getTextures()[1], hero.rects[position], dstrect);

        /*Updates the screen*/
        window.refresh();
        timeBuffer = timeBuffer + timeElapsed;

        /* update the animation*/
        if (timeBuffer > maxDuration) {
            timeBuffer = 0;
            index++;

            if (index >= current_hero_animation.size())
                index = 0;
        }

        auto t2 = Clock::now();

        elapsedNano = (double)(std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count());

        if (elapsedNano > 0) {
            double diff = ((1000000000.f / 60.f) - elapsedNano) / 1000000.f;

            if (diff > 0) {
                SDL_Delay((Uint32)diff);
            }
        }

        auto t3 = Clock::now();

        timeElapsed = (double)(std::chrono::duration_cast<std::chrono::nanoseconds>(t3 - t1).count()) / 1000000.f;

        /* update the screen */
        window.refresh();
    }

    window.cleanUp();
    for(auto e: entitiees)
        SDL_DestroyTexture(e.getText());
    SDL_DestroyTexture(window.getTextures()[0]);
    SDL_DestroyRenderer(window.getRenderer());
    SDL_Quit();

    return 0;
}