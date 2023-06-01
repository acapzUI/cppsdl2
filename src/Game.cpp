#include "Game.hpp"

#include "TextureManager.hpp"
//#include "TextManager.hpp"
#include "Map.hpp"
#include "ECS/Components.hpp"
#include "Vector2D.hpp"
#include "Collision.hpp"
#include "AssetManager.hpp"

#include <cstdlib>
#include <windows.h>

SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;
Manager manager;
Map *map;

SDL_Rect Game::camera = {0, 0, 480, 480};

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
auto &scoreEntity(manager.addEntity()); 

int score = 0;

auto &players(manager.getGroup(Game::groupPlayers));
auto &playerMissiles(manager.getGroup(Game::groupPlayerMissiles));
auto &enermys(manager.getGroup(Game::groupEnermy));
auto &enermyMissiles(manager.getGroup(Game::groupEnermyMissiles));
auto &coins(manager.getGroup(Game::groupCoins));
auto &uis(manager.getGroup(Game::groupUI));
auto &tiles(manager.getGroup(Game::groupMap));

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

    assets->AddFont("hiscore", "./assets/NewHiScore.ttf", 18);
    assets->AddFont("gothic", "./assets/NEXONLv1GothicBold.ttf", 24);
    assets->AddTexture("skull", "assets/item/item8BIT_skull.png");
    assets->AddTexture("coin", "assets/item/item8BIT_coin.png");
    assets->AddTexture("bg", "assets/black.png");
    assets->AddTexture("terrain", "assets/terrain_ss.png");
    assets->AddTexture("gem", "assets/item/item8BIT_gem.png"); 

    player.addComponent<TransformComponent>(10, 10, 32, 32, 1);
    player.addComponent<SpriteComponent>("gem");
    player.addComponent<KeyboardController>();
    player.addComponent<ColliderComponent>("player", 5, 5, 20, 25);
    player.addGroup(groupPlayers);

    map = new Map("terrain", 3, 32);
    map->LoadMap("assets/map/lv1.map", 25, 20);

    SDL_Color white = {.r=255, .g=255, .b=255};
    scoreEntity.addComponent<TextComponent>(300, 20, "score = 0", "gothic", white);
    scoreEntity.addGroup(groupUI);

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

int t = 0; // alarm
void Game::update() {
    manager.refresh();
    manager.update();

    // coin 생성
    if (t>2 && manager.getGroup(groupCoins).size() < 45) {
        //std::cout << manager.getGroup(groupCoins).size() << std::endl;
        auto &coinDummy(manager.addEntity());
        int xtmp = 40+(rand()%320);
        int ytmp = 40+(rand()%320);
        coinDummy.addComponent<TransformComponent>(xtmp, ytmp, 32, 32, 1);
        coinDummy.addComponent<SpriteComponent>("coin");
        coinDummy.addComponent<ColliderComponent>("coin", 10, 10, 15, 15);
        coinDummy.addComponent<ClickComponent>(0, 10, 10, 15, 15);
        coinDummy.addGroup(groupCoins);
        t=0;
    }
    t++;

    // coin - player collider 
    for (auto cc : coins) {
        if (Collision::AABB(player.getComponent<ColliderComponent>().collider, cc->getComponent<ColliderComponent>().collider)) {
            cc->destroy();
            score += 1;
            scoreEntity.getComponent<TextComponent>().SetLabelText("score = " + std::to_string(score), "gothic");
        }
    }

    // coin - click
    if (event.type == SDL_MOUSEBUTTONDOWN) { 
        for (auto cc : coins) {
            SDL_Rect clickR = cc->getComponent<ClickComponent>().destR;
            if (event.button.x >= clickR.x && event.button.x <= clickR.x+clickR.w && event.button.y >= clickR.y && event.button.y <= clickR.y+clickR.h) {   
                if (cc->getComponent<ClickComponent>().depth == uiDepth) {
                    cc->getComponent<ClickComponent>().onClickEvent();
                    cc->destroy();
                    printf("CLICKED.");
                }
            }
        }
    }

    camera.x = static_cast<int>(player.getComponent<TransformComponent>().position.x - 240);
    camera.y = static_cast<int>(player.getComponent<TransformComponent>().position.y - 240);

    // camera left border
    if (camera.x < 0) 
        camera.x = 0;
    if (camera.y < 0) 
        camera.y = 0;

    // camera right border
    if (camera.x > camera.w*2)
        camera.x = camera.w*2;
    if (camera.y > camera.h*2)
        camera.y = camera.h*2;
}

void Game::render() {
    SDL_RenderClear(renderer);
    mTextureManager.Draw(bgTexture, bgOrigin, bgSize, SDL_FLIP_NONE);
    
    for (auto t : tiles) {
        t->draw();
    } 
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
    for (auto ui : uis) {
        ui->draw();
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