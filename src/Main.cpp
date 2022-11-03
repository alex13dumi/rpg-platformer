#include <iostream>
#include <vector>
#include <chrono>
#include <cassert>
#include <SDL.h>
#include <SDL_surface.h>
#include <RenderWindow.hpp>
#include <Hero.hpp>

#define WIDTH 1280
#define HEIGHT 720
#define assertm(exp, msg) assert((msg, exp))
/*#define assertm(exp, msg) assert(((void)msg, exp))*/

typedef std::chrono::high_resolution_clock Clock;

int main(int argc, char* args[]) {
    /*Initializez SDL and creates a window*/
    RenderWindow window("GAME v1.0", WIDTH, HEIGHT);
    /*Load textures*/
    assertm(window.loadTextures(), "Couldn't load textures");

    /* Each sprite is an 50 x 37 images. TO DO: Store them in a JSON LUA data file*/
    Hero hero("John Baiat Bun", 100, 0, 10, 11, 7, 50, 37);
    /*Allocate memory for animations that are gonna be added for the hero*/
    hero.upload_animation();
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
        while(SDL_PollEvent(&event)) {
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
                switch (event.key.keysym.scancode) {
                    case SDL_SCANCODE_Q: current_hero_animation = hero.idle1; break;
                    case SDL_SCANCODE_W: current_hero_animation = hero.crouch; break;
                    case SDL_SCANCODE_D: current_hero_animation = hero.run; break;
                    case SDL_SCANCODE_R: current_hero_animation = hero.jump; break;
                    case SDL_SCANCODE_T: current_hero_animation = hero.mid; break;
                    case SDL_SCANCODE_Y: current_hero_animation = hero.fall; break;
                    case SDL_SCANCODE_U: current_hero_animation = hero.slide; break;
                    case SDL_SCANCODE_I: current_hero_animation = hero.grab; break;
                    case SDL_SCANCODE_O: current_hero_animation = hero.climb; break;
                    case SDL_SCANCODE_P: current_hero_animation = hero.idle2; break;
                    case SDL_SCANCODE_A: current_hero_animation = hero.attack1; break;
                    case SDL_SCANCODE_S: current_hero_animation = hero.attack2; break;
                    case SDL_SCANCODE_E: current_hero_animation = hero.attack3; break;
                    case SDL_SCANCODE_F: current_hero_animation = hero.hurt; break;
                    case SDL_SCANCODE_G: current_hero_animation = hero.die; break;
                    case SDL_SCANCODE_H: current_hero_animation = hero.jump; break;
                }
                index = 0;
            }
            hero.handleEvent(event);
        }
        hero.move();
        window.refresh();

        window.clear();
        /*After the event loop we can start the rendering*/
        size_t position = current_hero_animation[index].second + current_hero_animation[index].first * hero._col;
        SDL_Rect* dstrect;
        SDL_Rect dst = {256, 394, 120, 120};
        dstrect = &dst;
        //window.render(window.getTextures()[1], hero.rects[position], dstrect);
        hero.render(window, hero.frame_rects[position], dstrect);

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

    SDL_DestroyTexture(window.getTextures()[0]);
    SDL_DestroyRenderer(window.getRenderer());
    SDL_Quit();

    return 0;
}