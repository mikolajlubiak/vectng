#include "Game.hpp"
#include "ECS/Components.hpp"
#include "Map.hpp"
#include "TextureManager.hpp"

Map *map;

SDL_Renderer *Game::renderer = nullptr;

Manager manager;
auto &player(manager.addEntity());
auto &enemy(manager.addEntity());

Game::Game() {}
Game::~Game() {}

void Game::init(const char *title, int xpos, int ypos, Uint16 width,
                Uint16 height, SDL_WindowFlags flags) {

  if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
    std::cout << "Subsystems Initialised!" << std::endl;

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

  map = new Map();

  player.addComponent<PositionComponent>();
  player.addComponent<SpriteComponent>("Player/p1_front.png");

  enemy.addComponent<PositionComponent>(100, 100);
  enemy.addComponent<SpriteComponent>("Player/p2_front.png");
}

void Game::handleEvents() {
  SDL_Event event;
  SDL_PollEvent(&event);
  switch (event.type) {
  case SDL_QUIT:
    isRunning = false;
    break;
  default:
    break;
  }
}

void Game::update() {
  manager.refresh();
  manager.update();

  if (player.getComponent<PositionComponent>().x() > 100) {
    player.getComponent<SpriteComponent>().setTex("Player/p3_front.png");
  }
  /*std::cout << newPlayer.getComponent<PositionComponent>().x() << ","
            << newPlayer.getComponent<PositionComponent>().y() << std::endl;*/
}

void Game::render() {
  SDL_RenderClear(Game::renderer);
  map->DrawMap();
  manager.draw();
  SDL_RenderPresent(Game::renderer);
}

void Game::clean() {
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(Game::renderer);
  SDL_Quit();
  std::cout << "Game Cleaned!" << std::endl;
}
