//
// Created by asimion on 01.11.2022.
//

#ifndef SDL2TEST_ANIMATION_HPP
#define SDL2TEST_ANIMATION_HPP
#include<vector>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

class Animation{
public:
    Animation( std::vector<SDL_Rect*> anim_rects,  SDL_Rect* r_pos);
    void playAnimation(SDL_Renderer* renderer,SDL_Texture* texture, std::pair<size_t, size_t> frame, std::size_t sprite_col);
private:
    std::vector<SDL_Rect*> all_anim_rects;
    //std::vector<std::pair<std::size_t, std::size_t>> start_frame;
    SDL_Rect* new_randed_pos;

};
#endif //SDL2TEST_ANIMATION_HPP
