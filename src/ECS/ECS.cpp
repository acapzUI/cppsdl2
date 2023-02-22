#include "ECS/ECS.hpp"

void Entity::addGroup(Group mGroup) {
    groupBits et[mGroup] = true;
    manager.AddToGroup(this.mGroup);
}