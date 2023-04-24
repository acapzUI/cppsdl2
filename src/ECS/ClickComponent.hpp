#ifndef CLICKCOMPONENT_HPP
#define CLICKCOMPONENT_HPP

#include "SDL2/SDL.h"
#include "../Game.hpp"
#include "Components.hpp"

class ClickComponent : public Component {
public:
    void init() override {
        
    }

private:
    int depth; 
    int quads;
}


#endif