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
auto &wall(manager.addEntity());
auto &enemy(manager.addEntity());
auto &tile(manager.addEntity());

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

  player.addComponent<TransformComponent>(500.0f, 500.0f, 92, 66, 1);
  player.addComponent<SpriteComponent>("assets/Player/p1_front.png");
  player.addComponent<KeyboardController>();
  player.addComponent<ColliderComponent>("player");

  enemy.addComponent<TransformComponent>(100.0f, 100.0f, 92, 66, 1);
  enemy.addComponent<SpriteComponent>("assets/Player/p2_front.png");
  enemy.addComponent<ColliderComponent>("enemy");

  wall.addComponent<TransformComponent>(300.0f, 300.0f, 100, 100, 1);
  wall.addComponent<SpriteComponent>("assets/Tiles/dirt.png");
  wall.addComponent<ColliderComponent>("wall");

  tile.addComponent<TileComponent>(600, 600, 70, 70, 1);
  tile.addComponent<ColliderComponent>("water");
}

void Game::update() {
  manager.refresh();
  manager.update();
  enemy.getComponent<TransformComponent>().position.Add(Vector2D(2.0f, 2.0f));

  for (std::shared_ptr<ColliderComponent> coll : colliders) {
    if (Collision::AABB(player.getComponent<ColliderComponent>(), *coll) &&
        (player.getComponent<ColliderComponent>().tag != coll->tag)) {
      player.getComponent<TransformComponent>().velocity * -1;
    }
  }
}

void Game::render() {
  SDL_RenderClear(renderer);
  map->DrawMap();
  manager.draw();
  SDL_RenderPresent(renderer);
}

void Game::clean() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  std::cout << "Game Cleaned!" << std::endl;
}
