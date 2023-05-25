#ifndef ColliderComponent_hpp
#define ColliderComponent_hpp

#include <string>
#include "SDL2/SDL.h"
#include "Components.hpp"

class ColliderComponent : public Component {
public:
    SDL_Rect collider;
    std::string tag;

    SDL_Texture *tex;
    SDL_Rect srcR, destR;

    TransformComponent *transform;
    
    int xpos;
    int ypos;
    int width;
    int height;

    ColliderComponent(std::string t) {
        tag = t;
    }
    ColliderComponent(std::string t, int xx, int yy, int size) {
        tag = t;
        collider.x = xx;
        collider.y = yy;
        collider.w = collider.h = size;
    }
    ColliderComponent(std::string t, int xx, int yy, int ww, int hh) {
        tag = t;
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

        tex = TextureManager::LoadTexture("./assets/colliderborder.png"); 
        srcR = {0, 0, 32, 32};
        destR = {collider.x, collider.y, collider.w, collider.h};
    }
    void update() override {
        if (tag != "terrain") {
            collider.x = static_cast<int>(transform->position.x) + xpos;
            collider.y = static_cast<int>(transform->position.y) + ypos;
            collider.w = width * transform->scale;
            collider.h = height * transform->scale;
        }

        destR.x = collider.x - Game::camera.x;
        destR.y = collider.y - Game::camera.y;
        destR.w = collider.w;
        destR.h = collider.h;
    }

    void draw() override {
        //TextureManager::Draw(tex, srcR, destR, SDL_FLIP_NONE);
    }

};

#endif