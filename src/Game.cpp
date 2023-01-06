#include "Game.hpp"

SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Texture *bgTexture;
SDL_Texture *tx;
SDL_Rect bgOrigin = {0, 0, 10, 10};
SDL_Rect bgSize = {0, 0, 480, 480};
SDL_Rect txOrigin;
SDL_Rect txSize;

TextureManager mTextureManager;
TextManager mTextManager;

Manager manager;

// 엔티티임
auto &player(manager.addEntity());

// 이게 그룹임
enum groupLabels : std::size_t {
    groupPlayers,
    groupPlayerMissiles
    groupEnermy,
    groupEnermyMissiles,
    groupCoins,
    groupColliders,
};

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
        std::cout << "log : sdl_image init failed" << std::endl
            << IMG_GetError() << std::endl;
    } else {
        std::cout << "log : sdl_image initialized" << std::endl;
    }
    if (TTF_Init() < 0) {
        std::cout << "log : sdl_ttf init failed" << std::endl;
    } else {
        std::cout << "log : sdl_ttf initialized" << std::endl;
    }

    tx = mTextManager.LoadMessage("./assets/NewHiScore.ttf", "3050!", 45);
    SDL_Point txs;
    SDL_QueryTexture(tx, NULL, NULL, &txs.x, &txs.y);
    txOrigin = {0, 0, txs.x, txs.y};
    txSize = {10, 10, txs.x, txs.y};

    bgTexture = mTextureManager.LoadTexture("assets/black.png");
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
    manager.refresh();
    manager.update();
}

auto &tiles

void Game::render() {
    SDL_RenderClear(renderer);
    mTextureManager.Draw(bgTexture, bgOrigin, bgSize, SDL_FLIP_NONE);
    mTextureManager.Draw(tx, txOrigin, txSize, SDL_FLIP_NONE);
    pp->Render();
    SDL_RenderPresent(renderer);
}

void Game::clean() { 
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "log : game cleaned" << std::endl;
}