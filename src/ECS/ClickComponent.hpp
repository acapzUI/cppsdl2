#ifndef CLICKCOMPONENT_HPP
#define CLICKCOMPONENT_HPP

#include "SDL2/SDL.h"
#include "../Game.hpp"
#include "Components.hpp"

class ClickComponent : public Component {
public:
    void init() override {
        
    }
    void update() {
        if (Game::event.type == SDL_MOUSEBUTTONDOWN) { 
            if event.button.x 
        }
    }

private:
    int depth; 
    SDL_Rect size = {0, 0, 0, 0};
};

#endif