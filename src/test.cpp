#include <iostream>
#include <vector>
#include <chrono>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_surface.h>
#include <RenderWindow.hpp>
#include <Entity.hpp>
#include <System.hpp>
#include <Sprites.hpp>

#define WIDTH 1280
#define HEIGHT 720

typedef std::chrono::high_resolution_clock Clock;

bool init(){
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
    return true;
}

int main(int argc, char* args[]) {
    if(!init()){
        SDL_Log("Cannot initialize SDL ! ");
    }
    /*Creates a window*/
    RenderWindow window("GAME v1.0", WIDTH, HEIGHT);
    /*Load textures*/
    SDL_Texture *grassTexture = window.loadTexture("../res/gfx/grass.png");
    if (grassTexture == NULL){
        SDL_Log("Couldn't load grass texture !");
        return 1;
    }
    SDL_Texture* heroTexture = window.loadTexture("../res/gfx/adventurer-sheet.png");
    if (heroTexture == NULL){
        SDL_Log("Couldn't load main hero texture !");
        return 1;
    }

    std::vector<Entity> entitiees = {Entity( Vector2f(0, 120), grassTexture, Vector2f(8,8)),
                                     Entity( Vector2f(64, 120), grassTexture, Vector2f(8,8)),
                                     Entity( Vector2f(128, 120), grassTexture, Vector2f(8,8)),
                                     Entity( Vector2f(192, 120), grassTexture, Vector2f(8,8)),
                                     Entity( Vector2f(256, 120), grassTexture, Vector2f(8,8))};


    std::vector<SDL_Rect*> rects;
    /* Each sprite is an 50 x 37 images. TO DO: Store them in a JSON LUA data file*/
    Hero hero(11, 7, 50, 37);

    for (std::size_t i = 0; i < hero._row; i++) {
        for (std::size_t j = 0; j < hero._col; j++) {
            rects.push_back(new SDL_Rect{ (int) (j*hero._width), (int) (i * hero._height), (int) hero._width, (int) hero._height });
        }
    }
    Vector current = hero.idle1;
    size_t index = 0;

    double maxDuration = 150;
    double timeBuffer = 0;
    double timeElapsed = 0;
    SDL_Event event;
    bool gameRunning = true;

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
                    current = hero.idle1;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_W) {
                    current = hero.crouch;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_D) {
                    current = hero.run;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_R) {
                    current = hero.jump;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_T) {
                    current = hero.mid;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_Y) {
                    current = hero.fall;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_U) {
                    current = hero.slide;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_I) {
                    current = hero.grab;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_O) {
                    current = hero.climb;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_P) {
                    current = hero.idle2;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_A) {
                    current = hero.attack1;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_S) {
                    current = hero.attack2;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_E) {
                    current = hero.attack3;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_F) {
                    current = hero.hurt;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_G) {
                    current = hero.die;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_H) {
                    current = hero.jump;
                }
                index = 0;
            }
        }

        window.clear();
        /*After the event loop we can start the rendering*/
        for(auto e:entitiees)
            window.render(e);

        std::pair<size_t, size_t> currentPair = current[index];
        size_t position = currentPair.second + currentPair.first * hero._col;
        SDL_Rect * dstrect;
        SDL_Rect dst = {256, 394, 120, 120};
        dstrect = &dst;
        SDL_RenderCopy(window.getRenderer(), heroTexture, rects[position], dstrect);

        /*Updates the screen*/
        SDL_RenderPresent(window.getRenderer());

        timeBuffer = timeBuffer + timeElapsed;

        /* update the animation*/
        if (timeBuffer > maxDuration) {
            timeBuffer = 0;
            index++;

            if (index >= current.size())
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
        window.display();
    }

    window.cleanUp();
    for(auto e: entitiees)
        SDL_DestroyTexture(e.getText());
    SDL_DestroyTexture(heroTexture);
    SDL_DestroyRenderer(window.getRenderer());
    SDL_Quit();

    return 0;
}