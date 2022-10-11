#include "Player.hpp"
#include "TextureManager.hpp"

Player::Player() {

}

Player::Player(const char* texture, int x, int y) {
    sprite = TextureManager::LoadTexture(texture);
    xpos = x;
    ypos = y;
}

Player::~Player() {

}

