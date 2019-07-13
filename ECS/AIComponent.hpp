#ifndef AICOMPONENT_HPP_INCLUDED
#define AICOMPONENT_HPP_INCLUDED


#include "ECS.hpp"
#include "Components.hpp"
#include "../Vector2D.hpp"
#include <cmath>

//component contains all bot AI logic

extern Manager manager;

class AIComponent : public Component
{
public:
    TransformComponent* transform = nullptr;
    ColliderComponent* collider = nullptr;
    
    SDL_Rect result;
    Vector2D direction;
    uint16_t timer = 0;
    AIComponent()
    {
        
    }
    
    void init() override
    {
        //get other components
        if(entity->hasComponent<TransformComponent>())
            transform = &entity->getComponent<TransformComponent>();
        if(entity->hasComponent<ColliderComponent>())
            collider = &entity->getComponent<ColliderComponent>();

        direction = {0,0};
    }
    
    void update() override
    {   
        //get other colliders and puck
        auto& colliders(manager.getGroup(Game::groupColliders));
        auto& puck(manager.getGroup(Game::groupEnemies));

        //start timer
        timer++;

        for(auto p : puck)
        {
            //if puck is in ours half and last hit was more then 20 ticks ago
            if(p->getComponent<TransformComponent>().position.y < 450 && timer > 20)
            {
                //move towards puck
                direction.x = -(transform->position.x - p->getComponent<TransformComponent>().position.x) * 3;
                direction.y = -(transform->position.y - p->getComponent<TransformComponent>().position.y);
                //if distance to puck is less then 45 pixels - dont move
                if(sqrt(std::pow((transform->position.y-p->getComponent<TransformComponent>().position.y), 2) +
                    std::pow((transform->position.x - p->getComponent<TransformComponent>().position.x),2) < 45))
                    direction = {0,0};
                direction.Normalize();
            }
            if(p->getComponent<TransformComponent>().position.y > 450)
            {
                direction.x = -(transform->position.x - p->getComponent<TransformComponent>().position.x);
                direction.y = (transform->position.y - p->getComponent<TransformComponent>().position.y) * 3;
                direction.Normalize();
            }
            //if collides with puck and last hit was more then 20 ticks ago
            if(SDL_IntersectRect(&p->getComponent<ColliderComponent>().destR, &collider->destR, &result) == SDL_TRUE && timer > 20)
            {
                //go on opposite direction
                direction.x = -direction.x;
                direction.y = -direction.y;
                timer = 0;
            }
            
            
        }

        //collide with walls
        for (auto c : colliders)
        {
           if(SDL_IntersectRect(&c->getComponent<ColliderComponent>().destR, &collider->destR, &result) == SDL_TRUE)
           {
               if(c->getComponent<ColliderComponent>().tag == "Vterrain" || 
                    c->getComponent<ColliderComponent>().tag == "Hterrain" || 
                    c->getComponent<ColliderComponent>().tag == "mid")
               {
                   transform->position = transform->lastPosition;
               }
           }
        }

        //apply direction
        transform->velocity.x = direction.x;
        transform->velocity.y = direction.y;

    }

};

#endif