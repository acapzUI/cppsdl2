#include "Player.hpp"
#include "TextureManager.hpp"

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

    xpos += 1;
    ypos += 1;
    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = srcRect.w * 2;
    destRect.h = srcRect.h * 2;
}

void Player::Render() {
    SDL_RenderCopy(Game::renderer, sprite, &srcRect, &destRect);
}

