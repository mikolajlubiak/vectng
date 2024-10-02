#include "GameObject.hpp"
#include "TextureManager.hpp"

GameObject::GameObject(const char *textureSheet, uint_fast32_t x,
                       uint_fast32_t y)
    : xpos(x), ypos(y), objTexture(TextureManager::LoadTexture(textureSheet)),
      srcRect{0, 0, 0, 0}, destRect{0, 0, 0, 0} {}

void GameObject::Update() {
  xpos++;
  ypos++;

  srcRect.h = SPRITE_HEIGHT;
  srcRect.w = SPRITE_WIDTH;
  srcRect.x = 0;
  srcRect.y = 0;

  destRect.x = static_cast<int>(xpos);
  destRect.y = static_cast<int>(ypos);
  destRect.w = srcRect.w;
  destRect.h = srcRect.h;
}

void GameObject::Render() {
  SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}
