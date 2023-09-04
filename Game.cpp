#include "Game.hpp"
#include "Components.hpp"
#include "ECS.hpp"
#include "GameObject.hpp"
#include "Map.hpp"
#include "TextureManager.hpp"

GameObject *player;
GameObject *enemy;
Map *map;

SDL_Renderer *Game::renderer = nullptr;

Manager manager;
auto &newPlayer(manager.addEntity());

Game::Game() {}
Game::~Game() {}

void Game::init(const char *title, int xpos, int ypos, Uint16 width,
                Uint16 height, bool fullscreen) {
  Uint8 flags = 0;
  if (fullscreen) {
    flags = SDL_WINDOW_FULLSCREEN;
  }

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

  player = new GameObject("Player/p1_front.png", 0, 0);
  enemy = new GameObject("Player/p2_front.png", 100, 100);
  map = new Map();

  newPlayer.addComponent<PositionComponent>();
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
  player->Update();
  enemy->Update();
  manager.update();
  /*std::cout << newPlayer.getComponent<PositionComponent>().x() << ","
            << newPlayer.getComponent<PositionComponent>().y() << std::endl;*/
}

void Game::render() {
  SDL_RenderClear(Game::renderer);
  map->DrawMap();
  player->Render();
  enemy->Render();
  SDL_RenderPresent(Game::renderer);
}

void Game::clean() {
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(Game::renderer);
  SDL_Quit();
  std::cout << "Game Cleaned!" << std::endl;
}
