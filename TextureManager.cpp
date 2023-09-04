#include "TextureManager.hpp"

SDL_Texture* TextureManager::LoadTexture(const char *relativeFilePath)
{
    SDL_Surface *tmpSurface = IMG_Load(relativeFilePath);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);
    return texture;
}
