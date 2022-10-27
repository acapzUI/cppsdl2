#include "TextManager.hpp"

SDL_Texture *TextManager::LoadMessage(const char *f, const char *m, int size) {
    TTF_Font *font = TTF_OpenFont(f, size);
    if (!font) {
        std::cout << "log : font load failed" << std::endl;
    } else {
        std::cout << "log : font loaded" << std::endl;
    }

    SDL_Color textColor = {255, 255, 255};

    SDL_Surface *suf = TTF_RenderText_Solid(font, m, textColor);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer, suf);
    SDL_FreeSurface(suf);

    return tex; 
};