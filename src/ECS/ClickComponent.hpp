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

    TransformComponent *transform;
    int xpos, ypos, width, height = 0;

    int depth = -1;

    ClickComponent(int d, int xx, int yy, int ww, int hh) {
        depth = d;
        xpos = xx;
        ypos = yy;
        width = ww;
        height = hh;
    }

    void init() override {

        if (!entity->hasComponent<TransformComponent>()) {
            entity->addComponent<TransformComponent>();
        }
        transform = &entity->getComponent<TransformComponent>();

        tex = TextureManager::LoadTexture("./assets/clickborder.png"); 
        srcR = {0, 0, 32, 32};
        destR = {clickR.x, clickR.y, clickR.w, clickR.h};
        
    }
    void update() override {
        
        clickR.x = static_cast<int>(transform->position.x) + xpos;
        clickR.y = static_cast<int>(transform->position.y) + ypos;
        clickR.w = /*transform->width*/ width * transform->scale;
        clickR.h = /*transform->height*/ height * transform->scale;

        destR.x = clickR.x - Game::camera.x;
        destR.y = clickR.y - Game::camera.y;
        destR.w = clickR.w;
        destR.h = clickR.h;

        if (Game::event.type == SDL_MOUSEBUTTONDOWN) { 
            if (event.button.x >= clickR.x && event.button.x <= clickR.x+clickR.w && event.button.y >= clickR.y && event.button.y <= clickR.y+clickR.h) {
                
                //if (depth == Game::uiDepth) {
                    // todo : 

                //      }
                
               // todo : 
            }
        }
    }
    void setOnClickEvent() {

    }

    void draw() override {
        TextureManager::Draw(tex, srcR, destR, SDL_FLIP_NONE);
    }
};

#endif