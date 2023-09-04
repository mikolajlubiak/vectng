#include "Game.hpp"

Game *game = nullptr;

int main(int argc, const char* argv[])
{
    game = new Game;
    
    game->init("Gra z 2007", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, true);
    
    while(game->running())
    {
        game->handleEvents();
        game->update();
        game->render();
    }
    
    game->clean();
    
    return 0;
}
