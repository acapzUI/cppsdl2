#include "Collision.hpp"
#include "ECS/ColliderComponent.hpp"
#include <exception>

bool Collision::AABB(const SDL_Rect &recA, const SDL_Rect &recB) {
    return SDL_HasIntersection(&recA, &recB);
}

bool Collision::AABB(const ColliderComponent &colA, const ColliderComponent &colB) {
    if (AABB(colA.collider, colB.collider) && (colA.tag != colB.tag)) {
        if (colB.tag=="coin") {
            colB.entity->destroy();
            return true;
        }
    }    
    return false;
}