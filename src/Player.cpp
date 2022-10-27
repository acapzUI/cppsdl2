#include "Player.hpp"
#include "TextureManager.hpp"

Player::Player() {

}

Player::Player(const char* texture, int x, int y) {
    sprite = TextureManager::LoadTexture(texture);
    xpos = x;
    ypos = y;

    srcRect.h = 16;
    srcRect.w = 16;
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

    if (xpos<0 or xpos>464) {
        directionX = -directionX;
    }
    if (ypos<0 or ypos>404) {
        directionY = -directionY;
    }
}

void Player::Render() {
    SDL_RenderCopy(Game::renderer, sprite, &srcRect, &destRect);
}

