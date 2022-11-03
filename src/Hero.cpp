#include <Hero.hpp>

Hero::Hero(std::string name, uint8_t health, uint8_t speed, uint16_t attack, std::size_t row, std::size_t col, std::size_t width, std::size_t height):
_name(name), _health(health), _speed(speed), _attack(attack), _row(row), _col(col), _width(width), _height(height){
    posX = 0;
    posY = 0;
    velX = 0;
    velY = 0;
}

Hero::~Hero(){

}

void Hero::upload_animation(){
    for (std::size_t i = 0; i < _row; i++) {
        for (std::size_t j = 0; j < _col; j++) {
            frame_rects.push_back(new SDL_Rect{ (int) (j*_width), (int) (i * _height), (int) _width, (int) _height });
        }
    }
    SDL_Log("Uploaded Hero animation");
}

void Hero::handleEvent(SDL_Event &event){
    if(event.type == SDL_KEYDOWN && event.key.repeat == 0){
        switch (event.key.keysym.sym) {
            case SDLK_UP: velY -= VEL; break;
            case SDLK_DOWN: velY += VEL; break;
            case SDLK_LEFT: velX -= VEL; break;
            case SDLK_RIGHT: velX += VEL; break;
        }
    }
    else if(event.type == SDL_KEYUP && event.key.repeat == 0){
        switch (event.key.keysym.sym) {
            case SDLK_UP: velY += VEL; break;
            case SDLK_DOWN: velY -= VEL; break;
            case SDLK_LEFT: velX += VEL; break;
            case SDLK_RIGHT: velX += VEL; break;
        }
    }
}

void Hero::move(){
    //37 width of hero 50 height of hero
    //If the dot went too far to the left or right
    if( ( posX < 0 ) || ( posX + 37 > 1280 ) )
    {
        //Move back
        posX -= velX;
    }

    //Move the dot up or down
    posY += velY;

    //If the dot went too far up or down
    if( ( posY < 0 ) || ( posY + 50 > 720 ) )
    {
        //Move back
        posY -= velY;
    }
}

void Hero::render(RenderWindow window, SDL_Rect* src, SDL_Rect* dst)
{
    SDL_Texture* hero = window.loadTexture("../res/gfx/adventurer-sheet.png");
    if (hero == NULL){
        SDL_Log("Couldn't load main Hero !");
    }
    SDL_RenderCopy(window.getRenderer(), hero, src, dst);
}