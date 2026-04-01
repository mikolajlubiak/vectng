#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdint>
#include <memory>
#include <vector>

constexpr uint_fast32_t SPRITE_HEIGHT = 92;
constexpr uint_fast32_t SPRITE_WIDTH = 66;

inline constexpr const char *FLOOR_TILE_TAG = "floor_tile";

class ColliderComponent;

class Game {
public:
  void init(const char *title, int xpos, int ypos, int width, int height,
            bool fullscreen);

  void update(uint_fast32_t deltaTime);
  void render();
  void clean();
  [[nodiscard]] bool running() const { return isRunning; }

  static void AddTile(uint_fast32_t tileNumber, uint_fast32_t mapX,
                      uint_fast32_t mapY);

  static SDL_Renderer *renderer;
  static SDL_Event event;
  static bool isRunning;
  static std::vector<std::shared_ptr<ColliderComponent>> colliders;

private:
  SDL_Window *window = nullptr;
};
