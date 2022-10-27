#ifndef Player_hpp
#define Player_hpp

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>

class Player {
public:
    Player();
    Player(const char *texture, int x, int y);
    ~Player();
    void Render();
    void Update();
private:
    int xpos = 0;
    int ypos = 0;
    SDL_Texture* sprite;
    SDL_Rect srcRect, destRect;
    int directionX = 2;
    int directionY = 2;
};

#endif