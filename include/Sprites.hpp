//
// Created by alex13dumi on 10/18/22.
//

#ifndef SDL2TEST_SPRITES_HPP
#define SDL2TEST_SPRITES_HPP
#include <vector>
#include <cstddef>
struct Hero{
    std::size_t _row;
    std::size_t _col;
    std::size_t _width;
    std::size_t _height;

    std::vector<std::pair<std::size_t, std::size_t>> idle1  {{0, 0}, {0, 1}, {0, 2}, {0, 3}};
    std::vector<std::pair<std::size_t, std::size_t>> crouch {{0, 4}, {0, 5}, {0, 6}, {1, 0}};
    std::vector<std::pair<std::size_t, std::size_t>> run    {{1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6}};
    std::vector<std::pair<std::size_t, std::size_t>> jump   {{2, 0}, {2, 1}, {2, 2}, {2, 3}};
    std::vector<std::pair<std::size_t, std::size_t>> mid    {{2, 4}, {2, 5}, {2, 6}, {3, 0}};
    std::vector<std::pair<std::size_t, std::size_t>> fall   {{3, 1}, {3, 2}};
    std::vector<std::pair<std::size_t, std::size_t>> slide  {{3, 3}, {3, 4}, {3, 5}, {3, 6}, {4, 0}};
    std::vector<std::pair<std::size_t, std::size_t>> grab   {{4, 1}, {4, 2}, {4, 3}, {4, 4}};
    std::vector<std::pair<std::size_t, std::size_t>> climb  {{4, 5}, {4, 6}, {5, 0}, {5, 1}, {5, 2}};
    std::vector<std::pair<std::size_t, std::size_t>> idle2  {{5, 3}, {5, 4}, {5, 5}, {5, 6}};
    std::vector<std::pair<std::size_t, std::size_t>> attack1{{6, 0}, {6, 1}, {6, 2}, {6, 3}, {6, 4}};
    std::vector<std::pair<std::size_t, std::size_t>> attack2{{6, 5}, {6, 6}, {7, 0}, {7, 1}, {7, 2}, {7, 3}};
    std::vector<std::pair<std::size_t, std::size_t>> attack3{{7, 4}, {7, 5}, {7, 6}, {8, 0}, {8, 1}, {8, 2}};
    std::vector<std::pair<std::size_t, std::size_t>> hurt   {{8, 3}, {8, 4}, {8, 5}};
    std::vector<std::pair<std::size_t, std::size_t>> die    {{8, 6}, {9, 0}, {9, 1}, {9, 2}, {9, 3}, {9, 4}, {9, 5}};
    std::vector<std::pair<std::size_t, std::size_t>> jump2  {{9, 6}, {10, 0}, {10, 1}};

    Hero() = default;
    Hero(std::size_t row, std::size_t col, std::size_t widht, std::size_t height);
    
};
#endif //SDL2TEST_SPRITES_HPP
