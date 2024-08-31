#include "GameObject.hpp"
#include "TextureManager.hpp"

GameObject::GameObject(const char *textureSheet, float x, float y) {
  objTexture = TextureManager::LoadTexture(textureSheet);

  xpos = x;
  ypos = y;
}

void GameObject::Update() {
  xpos++;
  ypos++;

  srcRect.h = 92;
  srcRect.w = 66;
  srcRect.x = 0;
  srcRect.y = 0;

  destRect.x = xpos;
  destRect.y = ypos;
  destRect.w = srcRect.w;
  destRect.h = srcRect.h;
}

void GameObject::Render() {
  SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}
