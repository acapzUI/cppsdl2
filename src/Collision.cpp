#include "Collision.hpp"
#include "ECS/ColliderComponent.hpp"
#include <exception>

bool Collision::AABB(const SDL_Rect &recA, const SDL_Rect &recB) {
    return SDL_HasIntersection(&recA, &recB);
}

bool Collision::AABB(const ColliderComponent &colA, const ColliderComponent &colB) {
    if (AABB(colA.collider, colB.collider) && (colA.tag != colB.tag)) {
        //std::cout << colA.tag << " hit: " << colB.tag << std::endl;
        try {
            if (colA.tag=="player" && colB.tag=="coin") {
                colB.entity->destroy();
                return true;
            }
        } catch(std::exception &e) {
            
        }
    }
    return false;
}