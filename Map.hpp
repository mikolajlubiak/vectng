#pragma once
#include "Game.hpp"

class Map
{
public:
    Map();
    ~Map();
    
    void LoadMap(unsigned char[32][32]);
    void DrawMap();
private:
    SDL_Rect src, dest;
    SDL_Texture* dirt;
    SDL_Texture* grass;
    SDL_Texture* water;
    int map[32][32];
};