#include "EventHandler.hpp"

void EventHandler::handleInput(Entity* player)
{
    //get players transform component
    transform = &player->getComponent<TransformComponent>();
    
    while (SDL_PollEvent(&Game::event))
    {
        if(Game::event.type == SDL_QUIT)
            Game::isRunning = false;
        else if(Game::event.type == SDL_KEYDOWN)
        {
            switch(Game::event.key.keysym.sym)
            {
                //set players velocity according to input
                case SDLK_w:
                    transform->velocity.y = -1;
                    break;
                case SDLK_a:
                    transform->velocity.x = -1;
                    break;                    
                case SDLK_s:
                    transform->velocity.y = 1;
                    break;
                case SDLK_d:
                    transform->velocity.x = 1;
                    break;                    
                case SDLK_F1:
                    Game::drawColliders = !Game::drawColliders;
                    break;
                default:
                    break;
            }
        }
    
        else if(Game::event.type == SDL_KEYUP)
        {
            switch(Game::event.key.keysym.sym)
            {
                //set velocity back to 0 when key released
                case SDLK_w:
                    transform->velocity.y = 0;
                    break;
                case SDLK_a:
                    transform->velocity.x = 0;
                    break;                    
                case SDLK_s:
                    transform->velocity.y = 0;
                    break;
                case SDLK_d:
                    transform->velocity.x = 0;
                    break;                                                  
                case SDLK_ESCAPE:
                    Game::isRunning = false;
                default:
                    break;
            }
        }

        
    
    }
        
}