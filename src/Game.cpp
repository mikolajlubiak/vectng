#include "Game.hpp"
#include "Collision.hpp"
#include "ECS/Components.hpp"
#include "Map.hpp"
#include "TextureManager.hpp"
#include "Vector2D.hpp"

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
  ColliderGroup,
};

bool Game::isRunning = false;

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

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer) {
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      std::cout << "Renderer created!" << std::endl;
    }

    isRunning = true;
  } else {
    isRunning = false;
  }

  map = std::make_unique<Map>();

  Map::LoadMap("assets/Maps/tilemap16x16.txt", 16, 16);

  player.addComponent<TransformComponent>(500.0f, 500.0f, 92, 66, 1);
  player.addComponent<SpriteComponent>(
      "assets/Player/p1_spritesheet.png", "assets/Player/p1_spritesheet.txt",
      std::array<std::string, 2>{{"p1_stand", "p1_walk"}});
  player.addComponent<KeyboardController>();
  player.addComponent<ColliderComponent>("player");
  player.addGroup(playerGroup);

  enemy.addComponent<TransformComponent>(100.0f, 100.0f, 92, 66, 1);
  enemy.addComponent<SpriteComponent>(
      "assets/Player/p2_spritesheet.png", "assets/Player/p2_spritesheet.txt",
      std::array<std::string, 2>{{"p2_stand", "p2_walk"}});

  enemy.addComponent<ColliderComponent>("enemy");
  enemy.addGroup(enemyGroup);
}

void Game::update() {
  player.getComponent<TransformComponent>().old_positon =
      player.getComponent<TransformComponent>().position;

  manager.refresh();
  manager.update();

  if (player.getComponent<TransformComponent>().old_positon !=
      player.getComponent<TransformComponent>().position) {

    player.getComponent<SpriteComponent>().play("walk");

    if (player.getComponent<TransformComponent>().old_positon.x >
        player.getComponent<TransformComponent>().position.x) {
      player.getComponent<SpriteComponent>().spriteFlip = SDL_FLIP_HORIZONTAL;
    } else {
      player.getComponent<SpriteComponent>().spriteFlip = SDL_FLIP_NONE;
    }
  } else {
    player.getComponent<SpriteComponent>().play("idle");
  }

  enemy.getComponent<TransformComponent>().position.Add(Vector2D(2.0f, 2.0f));
  enemy.getComponent<SpriteComponent>().play("walk");

  for (std::shared_ptr<ColliderComponent> coll : colliders) {
    if (Collision::AABB(player.getComponent<ColliderComponent>(), *coll) &&
        (player.getComponent<ColliderComponent>().tag != coll->tag)) {

      Vector2D normalizedVelocity =
          player.getComponent<TransformComponent>().velocity;
      normalizedVelocity.Normalize();

      player.getComponent<TransformComponent>().position +=
          normalizedVelocity * -10;

      player.getComponent<TransformComponent>().velocity * -1;

      break;
    }
  }
}

auto &tiles(manager.getGroup(mapGroup));
auto &players(manager.getGroup(playerGroup));
auto &enemies(manager.getGroup(enemyGroup));

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

void Game::AddTile(tileType id, uint_fast32_t x, uint_fast32_t y) {
  auto &tile(manager.addEntity());
  tile.addComponent<TileComponent>(x, y, 68, 68, id);
  tile.addGroup(mapGroup);

  if (id == waterTile) {
    tile.addComponent<ColliderComponent>("water");
  }
}