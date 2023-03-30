#include "Map.h"
#include "Game.h"
#include <fstream>
#include "ECS/ECS.hpp"
#include "ECS/Components.hpp"

extern Manager manager;

Map::Map(std::string tID, int ms, int ts) : texID(tID), mapScale(ms), tileSize(ts) {
    scaleSize = ms * ts;
}

Map::~Map() {

}

void Map::LoadMap(std::string path, int sizeX, int SizeY) {
    char c;
    std::fstream mapFile;
    mapFile.open();

    int srcX, srcY;

    for (int y=0; y<sizeY; y++) {
        for (int x=0; x<sizeX; x++) {
            mapFile.get(c);
            srcY = atoi(&c) * tileSize;
            mapFile.get(c);
            srcX = atoi(&c) * tileSize;
            AddTile(srcX, srcY, x * scaled )
        }
    }
}