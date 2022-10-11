#include "Game.hpp"

SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;

Player *pp;

Game::Game() {

}
Game::~Game() {

}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen) {
    int flags = 0;
    if (fullscreen == true) {
        flags |= SDL_WINDOW_FULLSCREEN;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "log : init" << std::endl;
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (window) {
            std::cout << "log : window created" << std::endl;
        } else {
            std::cout << "log : window create failed" << std::endl;
        }
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "log : renderer created" << std::endl;
        } else {
            std::cout << "log : renderer create failed" << std::endl;
        }
        isRunning = true;
    } else {
        isRunning = false;
    }

    if (!IMG_Init(IMG_INIT_PNG)) {
        std::cout << "log : sdl_image not initialized. error : " << std::endl
            << IMG_GetError() << std::endl;
    } else {
        std::cout << "log : sdl_image initialized" << std::endl;
    }

    pp = new Player("./assets/sprite01.png", 30, 30);
}

void Game::handleEvents() {
    SDL_PollEvent(&event);
    switch (event.type) {
    case SDL_QUIT:
        isRunning = false;
        break;
    default:
        break;
    }
}

void Game::update() {

}

void Game::render() {
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "log : game cleaned" << std::endl;
}