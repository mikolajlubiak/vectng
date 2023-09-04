#pragma once
#include "Game.hpp"

class TextureManager
{
public:
    static SDL_Texture *LoadTexture(const char* fileName, SDL_Renderer* ren);
};