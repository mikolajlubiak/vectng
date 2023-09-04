#include "TextureManager.hpp"

SDL_Texture* TextureManager::LoadTexture(const char *fileName, SDL_Renderer *ren)
{
    SDL_Surface *tmpSurface = IMG_Load(fileName);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(ren, tmpSurface);
    SDL_FreeSurface(tmpSurface);
    return texture;
}
