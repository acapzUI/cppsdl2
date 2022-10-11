#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 480

#include "Game.hpp"
#include <iostream>

Game *game = nullptr;

enum {
    FPS = 60,
    frameDelay = 1000 / FPS
};

int main(int argc, char *argv[]) {
    std::cout << "log : main" << std::endl;
    Uint32 frameStart;
    int frameTime;

    game = new Game();
    game->init("123", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false);

    while (game->running()) {
        frameStart = SDL_GetTicks();

        game->handleEvents();
        game->update();
        game->render();

        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    game->clean();
    return 0;
}