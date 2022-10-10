#ifndef SDL2TEST_SYSTEM_HPP
#define SDL2TEST_SYSTEM_HPP
#include <SDL_cpuinfo.h>

class System{
public:
    System();
    ~System() = default;
    int getCores() const;
    int getRam() const;
    const char* getPlatform() const;
    SDL_bool get3d() const;
    SDL_bool getAltivec() const;
    SDL_bool getAvx() const;
    SDL_bool getMmx() const;

private:
    int _cores;
    int _ram;
    const char* _platform;
    SDL_bool _3d;
    SDL_bool _altivec;
    SDL_bool _avx;
    SDL_bool _mmx;
};
#endif