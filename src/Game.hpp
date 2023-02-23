#ifndef Game_hpp
#define Game_hpp

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <iostream>

#include "Player.hpp"
#include "TextureManager.hpp"
#include "TextManager.hpp"
#include "ECS/ECS.hpp"
#include "ECS/TransformComponent.hpp"
#include "ECS/SpriteComponent.hpp"
#include "ECS/Animation.hpp"

class Game {
public:
    Game();
    ~Game();

    void init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);

    void handleEvents();
    void update();
    void render();
    void clean();
    bool running() { return isRunning; }

    static SDL_Renderer *renderer;
    static SDL_Event event;
private:
    int cnt = 0;
    bool isRunning = false;
    SDL_Window *window;
};

#endif