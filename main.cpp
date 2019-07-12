#include "engine.hpp"

Game *game = nullptr;

int main(int argc, const char* argv[])
{
    //initialize game
    game = new Game();
    game->init("Air Hockey", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 958, 0);

    const int FPS = 60;
    const int frameDelay = 1000/ FPS;

    Uint32 frameStart;
    int frameTime;

    //game loop
    while(game->running())
    {
        frameStart = SDL_GetTicks();

        game->handleEvents();
        game->update();
        game->render();

        frameTime = SDL_GetTicks() - frameStart;

        if(frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    //on exit
    game->clean();
    return 0;
}
