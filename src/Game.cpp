#include "Game.hpp"
#include "Collision.hpp"
#include "ECS/Components.hpp"
#include "Map.hpp"
#include "TextureManager.hpp"
#include "Vector2D.hpp"
#include <algorithm>

std::unique_ptr<Map> map;

SDL_Renderer *Game::renderer = nullptr;

Manager manager;
SDL_Event Game::event;

std::vector<std::shared_ptr<ColliderComponent>> Game::colliders;

auto &player(manager.addEntity());
auto &enemy(manager.addEntity());

enum groupLabels : std::size_t {
  mapGroup,
  playerGroup,
  enemyGroup,
};

auto &tiles(manager.getGroup(mapGroup));
auto &players(manager.getGroup(playerGroup));
auto &enemies(manager.getGroup(enemyGroup));

bool Game::isRunning = false;

SDL_Rect Game::camera{0, 0, 0, 0};

void Game::init(const char *title, uint_fast32_t xpos, uint_fast32_t ypos,
                uint_fast32_t width, uint_fast32_t height, bool fullscreen) {
  if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
    std::cout << "Subsystems Initialised!" << std::endl;

    int flags = 0;

    if (fullscreen) {
      flags |= SDL_WINDOW_FULLSCREEN;
    }

    window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    if (window) {
      std::cout << "Window created!" << std::endl;
    }

    camera.w = width;
    camera.h = height;

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer) {
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      std::cout << "Renderer created!" << std::endl;
    }

    isRunning = true;
  } else {
    isRunning = false;
  }

  player.addComponent<TransformComponent>(20.0f, 500.0f, 92, 66, 1);
  player.addComponent<ColliderComponent>("player");
  player.addComponent<GravityComponent>();
  player.addComponent<CollisionResolver>();

  player.addComponent<SpriteComponent>(
      "assets/Player/p1_spritesheet.png", "assets/Player/p1_spritesheet.txt",
      std::array<std::string, 3>{{"p1_stand", "p1_walk", "p1_jump"}});

  player.addComponent<KeyboardController>();
  player.addGroup(playerGroup);

  enemy.addComponent<TransformComponent>(100.0f, 500.0f, 92, 66, 1);
  enemy.addComponent<ColliderComponent>("enemy");
  enemy.addComponent<GravityComponent>();
  enemy.addComponent<CollisionResolver>();

  enemy.addComponent<SpriteComponent>(
      "assets/Player/p2_spritesheet.png", "assets/Player/p2_spritesheet.txt",
      std::array<std::string, 3>{{"p2_stand", "p2_walk", "p2_jump"}});

  enemy.addGroup(enemyGroup);

  enemy.getComponent<TransformComponent>().velocity.x = 1.0f;
  enemy.getComponent<TransformComponent>().speed = 4;

  map = std::make_unique<Map>();
  Map::LoadMap("assets/Maps/tilemap50x10.txt", 50, 10);
}

void Game::update() {
  manager.refresh();
  manager.update();

  if (!enemy.getComponent<GravityComponent>().isInAir) {
    enemy.getComponent<TransformComponent>().velocity.y =
        enemy.getComponent<GravityComponent>().jumpVelocity;
    enemy.getComponent<GravityComponent>().isInAir = true;
  }

  camera.x = player.getComponent<TransformComponent>().position.x -
             (static_cast<float>(camera.w) / 2);
  camera.y = player.getComponent<TransformComponent>().position.y -
             (static_cast<float>(camera.h) / 2);

  camera.x = std::clamp(camera.x, 0, camera.w);
  camera.y = std::clamp(camera.y, 0, camera.h);
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
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  std::cout << "Game Cleaned!" << std::endl;
}

void Game::AddTile(const uint_fast32_t tileNumber, const uint_fast32_t mapX,
                   const uint_fast32_t mapY) {
  const std::string sprite_sheet_path = "assets/Tiles/tiles_spritesheet.png";
  constexpr uint_fast32_t tilemapRowSize = 12;
  constexpr uint_fast32_t tileSize = 72;
  constexpr std::array<uint_fast32_t, 2> floorTiles{104, 153};

  SDL_Rect gameMapTile;
  SDL_Rect tilemapTile;

  tilemapTile.x = tileSize * (tileNumber % tilemapRowSize);
  tilemapTile.y =
      tileSize * std::floor(static_cast<float>(tileNumber) / tilemapRowSize);
  tilemapTile.w = tileSize;
  tilemapTile.h = tileSize;

  gameMapTile.x = mapX * tileSize;
  gameMapTile.y = mapY * tileSize;
  gameMapTile.w = tileSize;
  gameMapTile.h = tileSize;

  auto &tile(manager.addEntity());

  tile.addComponent<TileComponent>(sprite_sheet_path, gameMapTile, tilemapTile);

  tile.addGroup(mapGroup);

  if (std::find(floorTiles.begin(), floorTiles.end(), tileNumber + 1) !=
      floorTiles.end()) {

    tile.addComponent<ColliderComponent>("floor_tile");
  }
}