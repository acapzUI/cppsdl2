#include "Game.hpp"

#include "TextureManager.hpp"
//#include "TextManager.hpp"
#include "ECS/Components.hpp"
#include "Vector2D.hpp"
#include "Collision.hpp"
#include "AssetManager.hpp"

#include <cstdlib>
#include <windows.h>

SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;
Manager manager;

std::vector<ColliderComponent *> Game::colliders;
AssetManager* Game::assets = new AssetManager(&manager);

SDL_Texture *bgTexture;
SDL_Texture *tx;
SDL_Rect bgOrigin = {0, 0, 10, 10};
SDL_Rect bgSize = {0, 0, 480, 480};
SDL_Rect txOrigin;
SDL_Rect txSize;

TextureManager mTextureManager;
//TextManager mTextManager;

auto &player(manager.addEntity());
auto &score(manager.addEntity()); 

enum groupLabels : std::size_t {
    groupPlayers,
    groupPlayerMissiles,
    groupEnermy,
    groupEnermyMissiles,
    groupCoins,
    groupColliders
};

auto &players(manager.getGroup(groupPlayers));
auto &playerMissiles(manager.getGroup(groupPlayerMissiles));
auto &enermys(manager.getGroup(groupEnermy));
auto &enermyMissiles(manager.getGroup(groupEnermyMissiles));
auto &coins(manager.getGroup(groupCoins));

Game::Game() {}
Game::~Game() {}

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

/*
    tx = mTextManager.LoadMessage("./assets/NewHiScore.ttf", "3050!", 45);
    SDL_Point txs;
    SDL_QueryTexture(tx, NULL, NULL, &txs.x, &txs.y);
    txOrigin = {0, 0, txs.x, txs.y};
    txSize = {10, 10, txs.x, txs.y};
*/

    assets->AddFont("hiscore", "./assets/NewHiScore.ttf", 45);
    assets->AddTexture("skull", "assets/item/item8BIT_skull.png");
    assets->AddTexture("coin", "assets/item/item8BIT_coin.png");
    assets->AddTexture("bg", "assets/black.png");

    player.addComponent<TransformComponent>(10, 10, 32, 32, 1);
    player.addComponent<SpriteComponent>("skull");
    player.addComponent<KeyboardController>();
    player.addComponent<ColliderComponent>("player", 24, 24);
    player.addGroup(groupPlayers);

    SDL_Color white = {.r=255, .g=255, .b=255};
    score.addComponent<TextComponent>(100, 20, "hiscore", white);

    bgTexture = assets->GetTexture("bg");
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

int t = 0;
void Game::update() {
    manager.refresh();
    manager.update();

    if (t>2 && manager.getGroup(groupCoins).size() < 45) {
        std::cout << manager.getGroup(groupCoins).size() << std::endl;
        auto &coinDummy(manager.addEntity());
        coinDummy.addComponent<TransformComponent>(40+(rand()%40), 40+(rand()%40), 32, 32, 1);
        coinDummy.addComponent<SpriteComponent>("coin");
        coinDummy.addComponent<ColliderComponent>("coin", 24, 24);
        coinDummy.addGroup(groupCoins);
        t=0;
    }
    t++;

    for (auto cc : coins) {
        if (Collision::AABB(player.getComponent<ColliderComponent>().collider, cc->getComponent<ColliderComponent>().collider)) {
            cc->destroy();
        }
    }
}



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