#include "Player.hpp"

Player::Player() {

}

Player::Player(const char* texture, int x, int y) {
    sprite = TextureManager::LoadTexture(texture);
    xpos = x;
    ypos = y;

    srcRect.h = 32;
    srcRect.w = 32;
    srcRect.x = 0;
    srcRect.y = 0;
}

Player::~Player() {

}

void Player::Update() {

    xpos += directionX;
    ypos += directionY;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = srcRect.w;
    destRect.h = srcRect.h;

    if (xpos<0 or xpos>452) {
        directionX = -directionX;
    }
    if (ypos<0 or ypos>392) {
        directionY = -directionY;
    }
}

void Player::Render() {
    SDL_RenderCopy(Game::renderer, sprite, &srcRect, &destRect);
}

