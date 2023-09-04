#ifndef Game_hpp
#define Game_hpp
#include <SDL2/SDL.h>
#include <iostream>

class Game {
public:
    Game();
    ~Game();
    
    void init(const char* title, unsigned int xpos, unsigned int ypos, unsigned int width, unsigned int height, bool fullscreen);
    
    void handleEvents();
    void update();
    void render();
    void clean();
   
    bool running() {return isRunning;}
    
private:
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;
    unsigned int cnt = 0;
    
};

#endif