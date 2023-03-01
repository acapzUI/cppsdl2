#include "TextureManager.hpp"

SDL_Texture *TextureManager::LoadTexture(const char *textureFile) {
    SDL_Surface *tempSurface = IMG_Load(textureFile);
    if (!tempSurface) {
        std::cout << "log : texture load failed" << std::endl;
    }
    SDL_Texture *tex =  SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
    SDL_FreeSurface(tempSurface); 
    
    return tex;
}

void TextureManager::Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip) {
    SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, 0, nullptr, flip);
}
void TextureManager::Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest, double angle, SDL_RendererFlip flip) {
    SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, angle, nullptr, flip);
}
void TextureManager::Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest, double angle, SDL_Point *point, SDL_RendererFlip flip) {
    SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, angle, point, flip);
}