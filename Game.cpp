#include "Game.hpp"

SDL_Texture *playerTexture;
SDL_Rect srcR, destR;

Game::Game()
{}
Game::~Game()
{}

void Game::init(const char* title, Uint32 xpos, Uint32 ypos, Uint16 width, Uint16 height, bool fullscreen)
{
    Uint8 flags = 0;
    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Subsystems Initialised!" << std::endl;

        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if(window)
        {
            std::cout << "Window created!" << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer)
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            std::cout << "Renderer created!" << std::endl;
        }

        isRunning = true;
    }
    else
    {
        isRunning = false;
    }
    
    SDL_Surface *tmpSurface = IMG_Load("Player/p1_front.png");
    playerTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);
    
}

void Game::handleEvents()
{
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

void Game::update()
{
    destR.h = 92;
    destR.w = 66;
    destR.x++;
}

void Game::render()
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, playerTexture, NULL, &destR);
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game Cleaned!" << std::endl;
}
