#include "Game.hpp"

#include "TextureManager.hpp"
#include "TextManager.hpp"
#include "ECS/Components.hpp"
#include "Collision.hpp"

#include <cstdlib>
#include <windows.h>

SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;

std::vector<ColliderComponent *> Game::colliders;

SDL_Texture *bgTexture;
SDL_Texture *tx;
SDL_Rect bgOrigin = {0, 0, 10, 10};
SDL_Rect bgSize = {0, 0, 480, 480};
SDL_Rect txOrigin;
SDL_Rect txSize;

TextureManager mTextureManager;
TextManager mTextManager;

Manager manager;

auto &player(manager.addEntity());

enum groupLabels : std::size_t {
    groupPlayers,
    groupPlayerMissiles,
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

    player.addComponent<TransformComponent>(10, 10);
    player.addComponent<SpriteComponent>("assets/item/item8BIT_skull.png");
    player.addComponent<KeyboardController>();
    player.addComponent<ColliderComponent>("player");
    player.addGroup(groupPlayers);

    bgTexture = mTextureManager.LoadTexture("assets/black.png");

    srand(GetTickCount());
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

int t=0;
void Game::update() {
    manager.refresh();

    if (t>20) {
        auto &coinDummy(manager.addEntity());
        coinDummy.addComponent<TransformComponent>(20+(rand()%420), 20+(rand()%420));
        coinDummy.addComponent<SpriteComponent>("assets/item/item8BIT_coin.png");
        coinDummy.addComponent<ColliderComponent>("coin");
        coinDummy.addGroup(groupCoins);
        t=0;
    }
    t++;

    for (auto cc : colliders) {
        if (Collision::AABB(player.getComponent<ColliderComponent>(), *cc)) {
            cc->entity->destroy();
        }
    }

    manager.update();
}

auto &players(manager.getGroup(groupPlayers));
auto &playerMissiles(manager.getGroup(groupPlayerMissiles));
auto &enermys(manager.getGroup(groupEnermy));
auto &enermyMissiles(manager.getGroup(groupEnermyMissiles));
auto &coins(manager.getGroup(groupCoins));

void Game::render() {
    SDL_RenderClear(renderer);
    mTextureManager.Draw(bgTexture, bgOrigin, bgSize, SDL_FLIP_NONE);
    
    for (auto p : players) {
        p->draw();
    }
    for (auto e : enermys) {
        e->draw();
    }
    for (auto pm : playerMissiles) {
        pm->draw();
    }
    for (auto em : enermyMissiles) {
        em->draw();
    }
    for (auto c : coins) {
        c->draw();
    }

    //mTextureManager.Draw(tx, txOrigin, txSize, SDL_FLIP_NONE);

    SDL_RenderPresent(renderer);
}

void Game::clean() { 
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "log : game cleaned" << std::endl;
}