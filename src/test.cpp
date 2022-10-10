#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <RenderWindow.hpp>
#include <Entity.hpp>
#include <System.hpp>

int main(int argc, char* args[])
{
    System CPU;
    SDL_Log("Platform: %s, RAM: %d MB", CPU.getPlatform(), CPU.getRam());

    if (SDL_Init(SDL_INIT_VIDEO) > 0)
        std::cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;

    if (!(IMG_Init(IMG_INIT_PNG)))
        std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;

    RenderWindow window("GAME v1.0", 1280, 720);

    SDL_Texture* grassTexture = window.loadTexture("../res/gfx/grass.png");
    SDL_Texture* adventurerTexture = window.loadTexture("../res/gfx/adventurer-sheet.png");

    std::vector<Entity> entitiees = {Entity( Vector2f(0, 120), grassTexture, Vector2f(8,8)),
                                     Entity( Vector2f(64, 120), grassTexture, Vector2f(8,8)),
                                     Entity( Vector2f(128, 120), grassTexture, Vector2f(8,8)),
                                     Entity( Vector2f(192, 120), grassTexture, Vector2f(8,8)),
                                     Entity( Vector2f(256, 120), grassTexture, Vector2f(8,8)),
                                     Entity( Vector2f(30, 0), adventurerTexture, Vector2f(2, 2))};

    bool gameRunning = true;

    SDL_Event event;

    /*Sprite animations: test*/
    std::vector<SDL_Rect> rects;
    /*Select the size of photo*/
    std::size_t nbRow = 11;
    std::size_t nbCol = 7;
    std::size_t widthSpr = 50;
    std::size_t heightSpr = 37;

    for(std::size_t i = 0; i < nbRow; i++)
        for(std::size_t j = 0; j < nbCol; j++)
            rects.push_back(SDL_Rect{ (int) (j*widthSpr), (int) (i * heightSpr), (int) widthSpr, (int) heightSpr });


    std::vector<std::pair<size_t, size_t>> idle1  { {0, 0}, {0, 1}, {0, 2}, {0, 3} };
    std::vector<std::pair<size_t, size_t>> crouch { {0, 4}, {0, 5}, {0, 6}, {1, 0} };
    std::vector<std::pair<size_t, size_t>> run    { {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6} };
    std::vector<std::pair<size_t, size_t>> jump   { {2, 0}, {2, 1}, {2, 2}, {2, 3} };
    std::vector<std::pair<size_t, size_t>> mid    { {2, 4}, {2, 5}, {2, 6}, {3, 0} };
    std::vector<std::pair<size_t, size_t>> fall   { {3, 1}, {3, 2} };
    std::vector<std::pair<size_t, size_t>> slide  { {3, 3}, {3, 4}, {3, 5}, {3, 6}, {4, 0} };
    std::vector<std::pair<size_t, size_t>> grab   { {4, 1}, {4, 2}, {4, 3}, {4, 4}};
    std::vector<std::pair<size_t, size_t>> climb  { {4, 5}, {4, 6}, {5, 0}, {5, 1}, {5, 2} };
    std::vector<std::pair<size_t, size_t>> idle2  { {5, 3}, {5, 4}, {5, 5}, {5, 6} };
    std::vector<std::pair<size_t, size_t>> attack1{ {6, 0}, {6, 1}, {6, 2}, {6, 3}, {6, 4} };
    std::vector<std::pair<size_t, size_t>> attack2{ {6, 5}, {6, 6}, {7, 0}, {7, 1}, {7, 2}, {7, 3} };
    std::vector<std::pair<size_t, size_t>> attack3{ {7, 4}, {7, 5}, {7, 6}, {8, 0}, {8, 1}, {8, 2} };
    std::vector<std::pair<size_t, size_t>> hurt   { {8, 3}, {8, 4}, {8, 5} };
    std::vector<std::pair<size_t, size_t>> die    { {8, 6}, {9, 0}, {9, 1}, {9, 2}, {9, 3}, {9, 4}, {9, 5} };
    std::vector<std::pair<size_t, size_t>> jump2  { {9, 6}, {10, 0}, {10, 1} };

    std::vector<std::pair<size_t, size_t>> current = idle1;
    size_t index = 0;

    double maxDuration = 150;
    double timeBuffer = 0;
    double timeElapsed = 0;

    while (gameRunning)
    {
       double elapsedNano = 0;
       auto t1 = std::chrono::high_resolution_clock::now();

        // Get our controls and events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                gameRunning = false;
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    gameRunning = false;
                else if (event.key.keysym.scancode == SDL_SCANCODE_Q)
                    current = idle1;
                else if (event.key.keysym.scancode == SDL_SCANCODE_W)
                    current = crouch;
                else if (event.key.keysym.scancode == SDL_SCANCODE_E)
                    current = run;
                else if (event.key.keysym.scancode == SDL_SCANCODE_R)
                    current = jump;
                else if (event.key.keysym.scancode == SDL_SCANCODE_T)
                    current = mid;
                else if (event.key.keysym.scancode == SDL_SCANCODE_Y)
                    current = fall;
                else if (event.key.keysym.scancode == SDL_SCANCODE_U)
                    current = slide;
                else if (event.key.keysym.scancode == SDL_SCANCODE_I)
                    current = grab;
                else if (event.key.keysym.scancode == SDL_SCANCODE_O)
                    current = climb;
                else if (event.key.keysym.scancode == SDL_SCANCODE_P)
                    current = idle2;
                else if (event.key.keysym.scancode == SDL_SCANCODE_A)
                    current = attack1;
                else if (event.key.keysym.scancode == SDL_SCANCODE_S)
                    current = attack2;
                else if (event.key.keysym.scancode == SDL_SCANCODE_D)
                    current = attack3;
                else if (event.key.keysym.scancode == SDL_SCANCODE_F)
                    current = hurt;
                else if (event.key.keysym.scancode == SDL_SCANCODE_G)
                    current = die;
                else if (event.key.keysym.scancode == SDL_SCANCODE_H)
                    current = jump;
            }
            index = 0;
        }
        window.clear();

        for (Entity& e : entitiees)
        {
            window.render(e);
        }
        window.display();
    }

    window.cleanUp();
    SDL_Quit();

    return 0;
}