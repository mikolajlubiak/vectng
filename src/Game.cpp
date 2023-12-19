#include "Game.hpp"
#include "ECS/Components.hpp"
#include "Map.hpp"
#include "TextureManager.hpp"
#include "Vector2D.hpp"
#include "Collision.hpp"

Map *map;

SDL_Renderer *Game::renderer = nullptr;

Manager manager;
SDL_Event Game::event;
auto &player(manager.addEntity());
auto &wall(manager.addEntity());
auto &enemy(manager.addEntity());

Game::Game() {}
Game::~Game() {}

void Game::init(const char *title, uint_fast32_t xpos, uint_fast32_t ypos, uint_fast16_t width, uint_fast16_t height, bool fullscreen) {
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystems Initialised!" << std::endl;

		int flags = 0;

		if (fullscreen) {
			flags = SDL_WINDOW_FULLSCREEN;
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

	map = new Map();

	player.addComponent<TransformComponent>();
	player.addComponent<SpriteComponent>("assets/Player/p1_front.png");
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");

	enemy.addComponent<TransformComponent>(100.0f, 100.0f);
	enemy.addComponent<SpriteComponent>("assets/Player/p2_front.png");
	enemy.addComponent<ColliderComponent>("enemy");
	
	wall.addComponent<TransformComponent>(300.0f, 300.0f, 200, 200, 1);
	wall.addComponent<SpriteComponent>("assets/Tiles/dirt.png");
	wall.addComponent<ColliderComponent>("wall");
}

void Game::update() {
	manager.refresh();
	manager.update();
	enemy.getComponent<TransformComponent>().position.Add(Vector2D((uint_fast32_t)3, (uint_fast32_t)2));
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
