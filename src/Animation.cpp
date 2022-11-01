//
// Created by asimion on 01.11.2022.
//
#include<Animation.hpp>

Animation::Animation(std::vector<SDL_Rect *> anim_rects, SDL_Rect *r_pos) {
            all_anim_rects = std::move(anim_rects);
            new_randed_pos = r_pos;
}

void Animation::playAnimation(SDL_Renderer *renderer, SDL_Texture *texture, std::pair<size_t, size_t> frame, std::size_t sprite_col) {
    std::pair<size_t, size_t> curr_frame = frame;
    size_t position = curr_frame.second + curr_frame.first * sprite_col;
    SDL_RenderCopy(renderer, texture, all_anim_rects[position], new_randed_pos);
}