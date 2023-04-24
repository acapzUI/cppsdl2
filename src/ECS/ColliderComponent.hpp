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
    
    int xborder;
    int yborder;
    int width;
    int height;

    //int width, height = 0;

    ColliderComponent(std::string t) {
        tag = t;
    }
    /*
    ColliderComponent(std::string t, int w, int h) {
        tag = t;
        width = w;
        height = h;
    }
    */
    ColliderComponent(std::string t, int xpos, int ypos, int size) {
        tag = t;
        collider.x = xpos;
        collider.y = ypos;
        collider.w = collider.h = size;
    }
    ColliderComponent(std::string t, int xpos, int ypos, int collwidth, int collheight) {
        tag = t;
        xborder = xpos;
        yborder = ypos;
        width = collwidth;
        height = collheight;
    }
    void init() override {
        if (!entity->hasComponent<TransformComponent>()) {
            entity->addComponent<TransformComponent>();
        }
        transform = &entity->getComponent<TransformComponent>();
        /*Game::colliders.push_back(this);
        collider.w = static_cast<int>(width);
        collider.h = static_cast<int>(height);*/

        tex = TextureManager::LoadTexture("./assets/colliderborder.png"); 
        srcR = {0, 0, 32, 32};
        destR = {collider.x, collider.y, collider.w, collider.h};

        /*collider.w = static_cast<int>(transform->width * transform->scale);
        collider.h = static_cast<int>(transform->height * transform->scale);*/
    }
    void update() override {
        
        if (tag != "terrain") {
            collider.x = static_cast<int>(transform->position.x) + xborder;
            collider.y = static_cast<int>(transform->position.y) + yborder;
            collider.w = /*transform->width*/ width * transform->scale;
            collider.h = /*transform->height*/ height * transform->scale;
        }

        destR.x = collider.x - Game::camera.x;
        destR.y = collider.y - Game::camera.y;
        destR.w = collider.w;
        destR.h = collider.h;

        /*collider.x = static_cast<int>(transform->position.x);
        collider.y = static_cast<int>(transform->position.y);*/
        /*collider.w = static_cast<int>(width);
        collider.h = static_cast<int>(height);*/
        /*collider.w = static_cast<int>(transform->width * transform->scale);
        collider.h = static_cast<int>(transform->height * transform->scale);*/
    }

    void draw() override {
        TextureManager::Draw(tex, srcR, destR, SDL_FLIP_NONE);
    }

};

#endif