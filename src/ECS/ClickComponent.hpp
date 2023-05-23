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
    SDL_Rect srcR, destR;
    SDL_Rect clickR = {0, 0, 0, 0};

    int xpos, ypos, width, height = 0;


    ClickComponent(int d, int xx, int yy, int ww, int hh) {
        depth = d;

        xpos = xx;
        ypos = yy;
        width = ww;
        height = hh;
        
    }

    void init() override {

        tex = TextureManager::LoadTexture("./assets/clickborder.png"); 
        srcR = {0, 0, 32, 32};
        destR = {click.x, size.y, size.w, size.h};

        if (!entity->hasComponent<TransformComponent>()) {
            entity->addComponent<TransformComponent>();
        }
        transform = &entity->getComponent<TransformComponent>();
        
    }
    void update() override {
        
        
        clickR.x = static_cast<int>(transform->position.x) + xborder;
        clickR.y = static_cast<int>(transform->position.y) + yborder;
        clickR.w = /*transform->width*/ width * transform->scale;
        clickR.h = /*transform->height*/ height * transform->scale;

        destR.x = clickR.x - Game::camera.x;
        destR.y = clickR.y - Game::camera.y;
        destR.w = clickR.w;
        destR.h = clickRS.h;

        /*
        if (Game::event.type == SDL_MOUSEBUTTONDOWN) { 
            if (event.button.x >= size.x && event.button.x <= size.x+size.w && event.button.y >= size.y && event.button.y <= size.y+size.h) {
                
                //if (depth == Game::uiDepth) {
                    // todo : 

                //      }
                
               // todo : 
            }
        }
        */
    }
    void draw() override {
        TextureManager::Draw(tex, srcR, destR, SDL_FLIP_NONE);
    }

private:
    int depth;

};

#endif