#ifndef CLICKCOMPONENT_HPP
#define CLICKCOMPONENT_HPP

#include "SDL2/SDL.h"
#include "../Game.hpp"
#include "Components.hpp"


// 23.04.26
// 클릭했을때 ui의 click event를 check해야되는데
// 한 화면에 여러개의 버튼이 있을수도 있는거 아니냐?
// ui를 한꺼번에 관리하는 class 하나랑,
// button click event 관리하는 sub-class 하나 <- this class

class ClickComponent : public Component {
public:

    SDL_Texture *tex;
    SDL_Rect srcRect, destRect;
    SDL_Rect size = {x=0, y=0, w=0, h=0};


    ClickComponent(int d, int xpos, int ypos, int width, int height) {
        depth = d;
        size.x = xpos;
        size.y = ypos;
        size.w = width;
        size.h = height;
    }

    void init() override {

        tex = TextureManager::LoadTexture("./assets/clickborder.png"); 
        srcRect = {0, 0, 32, 32};
        destRect = {size.x, size.y, size.w, size.h};
        
    }
    void update() override {
        /*
        if (Game::event.type == SDL_MOUSEBUTTONDOWN) { 
            if (event.button.x >= size.x && event.button.x <= size.x+size.w && event.button.y >= size.y && event.button.y <= size.y+size.h) {
                
                //if (depth == Game::uiDepth) {
                    // todo : 

                //}
                
               // todo : 
            }
        }
        */
    }
    void draw() override {
        TextureManager::Draw(tex, srcRect, destRect, SDL_FLIP_NONE);
    }

private:
    int depth;

};

#endif