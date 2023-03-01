#ifndef TextureManager_hpp
#define TextureManager_hpp

#include "Game.hpp"

class TextureManager {
public:
    static SDL_Texture *LoadTexture(const char *textureFile);
    static void Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip);  
    static void Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest, double angle, SDL_RendererFlip flip);  
    static void Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest, double angle, SDL_Point *point, SDL_RendererFlip flip);  

};

#endif