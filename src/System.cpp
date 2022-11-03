#include <System.hpp>

System::System(): _cores(SDL_GetCPUCount()), _ram(SDL_GetSystemRAM()), _3d(SDL_Has3DNow()), _altivec(SDL_HasAltiVec()), _avx(SDL_HasAVX()), _mmx(SDL_HasMMX()) { }
int System::getCores() const{ return _cores; }
int System::getRam() const{ return  _ram; }
const char* System::getPlatform() const { return SDL_GetPlatform(); }
SDL_bool System::get3d() const{ return _3d; }
SDL_bool System::getAltivec() const{ return _altivec; }
SDL_bool System::getAvx() const { return _avx; }
SDL_bool System::getMmx() const { return _mmx; }