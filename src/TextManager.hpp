#ifndef TextManager_hpp
#define TextManager_hpp

#include "Game.hpp"

class TextManager {
public:
    static SDL_Texture *LoadMessage(const char *f, const char *m, int size);
};

#endif