#include "Game.hpp"
#include "Collision.hpp"
#include "ECS/Components.hpp"
#include "Map.hpp"
#include "TextureManager.hpp"
#include "Vector2D.hpp"
#include <iostream>

SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event{};
bool Game::isRunning = false;
std::vector<std::shared_ptr<ColliderComponent>> Game::colliders;

Manager manager{};

auto &player(manager.addEntity());
auto &enemy(manager.addEntity());

enum GroupLabels : std::size_t {
  kMapGroup,
  kPlayerGroup,
  kEnemyGroup,
};

auto &tiles(manager.getGroup(kMapGroup));
auto &players(manager.getGroup(kPlayerGroup));
auto &enemies(manager.getGroup(kEnemyGroup));

Vector2D initialPlayerPos{20.0f, 500.0f};

void Game::init(const char *title, int xpos, int ypos, int width, int height,
                bool fullscreen) {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
    isRunning = false;
    return;
  }

  int flags = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;

  window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
  if (!window) {
    std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
    isRunning = false;
    return;
  }

  renderer = SDL_CreateRenderer(window, -1, 0);
  if (!renderer) {
    std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
    isRunning = false;
    return;
  }

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  isRunning = true;

  player.addComponent<TransformComponent>(
      initialPlayerPos.x, initialPlayerPos.y, SPRITE_HEIGHT, SPRITE_WIDTH, 1u);
  player.addComponent<ColliderComponent>("player");
  player.addComponent<GravityComponent>();
  player.addComponent<ScrollComponent>(
      player.getComponentPtr<TransformComponent>(), initialPlayerPos);
  player.addComponent<SpriteComponent>(
      "assets/Player/p1_spritesheet.png", "assets/Player/p1_spritesheet.txt",
      std::array<std::string, 3>{{"p1_stand", "p1_walk", "p1_jump"}});
  player.addComponent<KeyboardController>();
  player.addGroup(kPlayerGroup);

  enemy.addComponent<TransformComponent>(100.0f, 500.0f, SPRITE_HEIGHT,
                                         SPRITE_WIDTH, 1u);
  enemy.addComponent<ColliderComponent>("enemy");
  enemy.addComponent<GravityComponent>();
  enemy.addComponent<ScrollComponent>(
      player.getComponentPtr<TransformComponent>(), initialPlayerPos);
  enemy.addComponent<SpriteComponent>(
      "assets/Player/p2_spritesheet.png", "assets/Player/p2_spritesheet.txt",
      std::array<std::string, 3>{{"p2_stand", "p2_walk", "p2_jump"}});
  enemy.addGroup(kEnemyGroup);

  enemy.getComponent<TransformComponent>().velocity.x = 1.0f;
  enemy.getComponent<TransformComponent>().speed = 0.2f;

  Map::LoadMap("assets/Maps/tilemap50x10.txt", 50, 10);
}

void Game::update(uint_fast32_t step) {
  manager.refresh();
  manager.update(step);
}

void Game::render() {
  SDL_RenderClear(renderer);

  for (auto &t : tiles) {
    t->draw();
  }
  for (auto &p : players) {
    p->draw();
  }
  for (auto &e : enemies) {
    e->draw();
  }

  SDL_RenderPresent(renderer);
}

void Game::clean() {
  TextureManager::Cleanup();
  SDL_DestroyRenderer(renderer);
  renderer = nullptr;
  SDL_DestroyWindow(window);
  window = nullptr;
  SDL_Quit();
}

void Game::AddTile(uint_fast32_t tileNumber, uint_fast32_t mapX,
                   uint_fast32_t mapY) {
  constexpr uint_fast32_t kTilemapRowSize = 12;
  constexpr uint_fast32_t kTileSize = 72;
  constexpr std::array<uint_fast32_t, 2> kFloorTiles{104, 153};

  const std::string sprite_sheet_path = "assets/Tiles/tiles_spritesheet.png";

  SDL_Rect tilemapTile;
  tilemapTile.x = static_cast<int>(kTileSize * (tileNumber % kTilemapRowSize));
  tilemapTile.y = static_cast<int>(kTileSize * (tileNumber / kTilemapRowSize));
  tilemapTile.w = kTileSize;
  tilemapTile.h = kTileSize;

  SDL_Rect gameMapTile;
  gameMapTile.x = static_cast<int>(mapX * kTileSize);
  gameMapTile.y = static_cast<int>(mapY * kTileSize);
  gameMapTile.w = kTileSize;
  gameMapTile.h = kTileSize;

  auto &tile(manager.addEntity());

  tile.addComponent<ScrollComponent>(
      player.getComponentPtr<TransformComponent>(), initialPlayerPos);
  tile.addComponent<TileComponent>(sprite_sheet_path, gameMapTile, tilemapTile);
  tile.addGroup(kMapGroup);

  if (std::find(kFloorTiles.begin(), kFloorTiles.end(), tileNumber + 1) !=
      kFloorTiles.end()) {
    tile.addComponent<ColliderComponent>(FLOOR_TILE_TAG);
  }
}
