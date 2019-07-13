#include "engine.hpp"
#include "TextureManager.hpp"


#include "ECS/Components.hpp"
#include "Vector2D.hpp"

#include "Collision.hpp"

#include "EventHandler.hpp"


EventHandler handler;
Manager manager;

SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;
Vector2D Game::score = {0,0};

bool Game::isRunning = false;
bool Game::drawColliders = false;

//creating entities

auto& player(manager.addEntity());
auto& enemy(manager.addEntity());
auto& puck(manager.addEntity());
auto& map(manager.addEntity());
auto& midCollider(manager.addEntity());
auto& leftWall(manager.addEntity());
auto& rightWall(manager.addEntity());
auto& upWall(manager.addEntity());
auto& downWall(manager.addEntity());
auto& upHitbox(manager.addEntity());
auto& downHitbox(manager.addEntity());
auto& scoreLabel(manager.addEntity());

//getting groups of entities
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& maps(manager.getGroup(Game::groupMap));

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;
    windowH = height;
    windowW = width;
    if(fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        //initialising subsystems
        //creating window
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        //creating renderer
        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);            
        }
        isRunning = true;
    } 
    else 
    {
        //if failed - exit
        isRunning = false;
    }
    //init fonts
    TTF_Init();


    //adding components to entities

    //background image
    map.addComponent<TransformComponent>(0, 0, 479, 320, 2);
    map.addComponent<SpriteComponent>("assets/board.png");
    map.addGroup(groupMap);
    
    //walls
    midCollider.addComponent<TransformComponent>(0, 472, 5, 640, 1);
    midCollider.addComponent<ColliderComponent>("mid");
    midCollider.addGroup(groupColliders);

    leftWall.addComponent<TransformComponent>(0, 0, 958, 20, 1);
    leftWall.addComponent<ColliderComponent>("Vterrain");
    leftWall.addGroup(groupColliders);

    rightWall.addComponent<TransformComponent>(620, 0, 958, 20, 1);
    rightWall.addComponent<ColliderComponent>("Vterrain");
    rightWall.addGroup(groupColliders);

    upWall.addComponent<TransformComponent>(0, 0, 20, 640, 1);
    upWall.addComponent<ColliderComponent>("Hterrain");
    upWall.addGroup(groupColliders);

    downWall.addComponent<TransformComponent>(0, 938, 20, 640, 1);
    downWall.addComponent<ColliderComponent>("Hterrain");
    downWall.addGroup(groupColliders);

    //hitboxes
    upHitbox.addComponent<TransformComponent>(170, 20, 3, 300, 1);
    upHitbox.addComponent<ColliderComponent>("upHitbox");
    upHitbox.addGroup(groupColliders);

    downHitbox.addComponent<TransformComponent>(170, 935, 3, 300, 1);
    downHitbox.addComponent<ColliderComponent>("downHitbox");
    downHitbox.addGroup(groupColliders);

    //player
    player.addComponent<TransformComponent>(280, 850, 62, 62, 1);
    player.addComponent<SpriteComponent>("assets/p1.png");
    player.addComponent<ColliderComponent>("player");
    player.addGroup(groupColliders);
    
    //bot
    enemy.addComponent<TransformComponent>(280, 50, 62, 62, 1);
    enemy.addComponent<SpriteComponent>("assets/p2.png");
    enemy.addComponent<ColliderComponent>("player");
    enemy.addComponent<AIComponent>();
    enemy.addGroup(groupColliders);
    
    //puck
    puck.addComponent<TransformComponent>(300, 459, 42, 42, 1);
    puck.addComponent<SpriteComponent>("assets/p_sheet.png", true);
    puck.addComponent<ColliderComponent>("puck");
    puck.addComponent<ProjectileComponent>(15, 0, 0);
    puck.addGroup(groupColliders);
    puck.addGroup(groupEnemies);

    //score 
    scoreLabel.addComponent<UILabel>(20, 20, 30, "Player 0 - 0 Bot", "assets/font.ttf");
 
}

void Game::handleEvents()
{
    //handle user input 
    handler.handleInput(&player);
}

void Game::update()
{
    //update all entities and their components
    manager.refresh();
    manager.update();
    
    Vector2D pVel = player.getComponent<TransformComponent>().velocity;
    if(pVel.x != 0 && pVel.y != 0)    
        player.getComponent<TransformComponent>().speed = 4;    
    else
        player.getComponent<TransformComponent>().speed = 6;
    

    for (auto c : colliders)
    {   //if player collides with walls
        if(Collision::AABB(c->getComponent<ColliderComponent>().destR, player.getComponent<ColliderComponent>().destR))
        {
            if(c->getComponent<ColliderComponent>().tag == "Vterrain" || 
                c->getComponent<ColliderComponent>().tag == "Hterrain" || 
                c->getComponent<ColliderComponent>().tag == "mid"   
               
            )
            {   //stop moving
                player.getComponent<TransformComponent>().position = player.getComponent<TransformComponent>().lastPosition;
            }
        }
    }
    
    

}



void Game::render()
{
    SDL_RenderClear(renderer);
    for(auto* m : maps)
    {
        m->draw();
    }

    for (auto& c : colliders)
    {
        c->draw();
    }    
    scoreLabel.draw();
    SDL_RenderPresent(renderer);

}

void Game::clean()
{
    //on exit
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

bool Game::running()
{
    return isRunning;
}

