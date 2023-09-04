#include "TextureManager.hpp"

SDL_Texture* TextureManager::LoadTexture(const char *relativeFilePath, SDL_Renderer *ren)
{
    SDL_Surface *tmpSurface = IMG_Load(relativeFilePath);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(ren, tmpSurface);
    SDL_FreeSurface(tmpSurface);
    return texture;
}
