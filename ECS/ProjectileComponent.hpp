#ifndef PROJECTILECOMPONENT_HPP_INCLUDED
#define PROJECTILECOMPONENT_HPP_INCLUDED


#include "ECS.hpp"
#include "Components.hpp"
#include "../Vector2D.hpp"
#include "../engine.hpp"
#include "../audio.hpp"

//component contains pucks logic 

extern Manager manager;

class ProjectileComponent : public Component
{
public:
    int speed;
    Vector2D direction;

    TransformComponent* transform = nullptr;
    ColliderComponent* collider = nullptr;
    
    SDL_Rect result;

    Audio audioPaddleHit;
    Audio audioGoal;

   


    ProjectileComponent (int spd, float dx, float dy)
    {
        speed = spd;
        direction = { dx, dy };
        audioPaddleHit.load("assets/hit.wav");
        audioGoal.load("assets/goal.wav");
    }
    
    ~ProjectileComponent(){}

    void init() override
    {
        //get other components
        if(entity->hasComponent<TransformComponent>())
            transform = &entity->getComponent<TransformComponent>();
        if(entity->hasComponent<ColliderComponent>())
            collider = &entity->getComponent<ColliderComponent>();

    }
    void update() override
    {
        //get colliders
        auto& colliders(manager.getGroup(Game::groupColliders));
        
        
        //bounce logic
        for (auto c : colliders)
        {
           if(SDL_IntersectRect(&c->getComponent<ColliderComponent>().destR, &collider->destR, &result) == SDL_TRUE)
           {
               //if wall is vertical - invert X direction
               if(c->getComponent<ColliderComponent>().tag == "Vterrain")
               {
                    audioPaddleHit.play();
                    transform->position = transform->lastPosition;
                    direction.x = -direction.x;
               }
               //if wall if horizontal - invert Y direction
               if(c->getComponent<ColliderComponent>().tag == "Hterrain")
               {
                    audioPaddleHit.play();
                    transform->position = transform->lastPosition;
                    direction.y = -direction.y;
               }
               //if collides with player
               if(c->getComponent<ColliderComponent>().tag == "player")
               {
                    audioPaddleHit.play();
                    //get new direction based on players position

                    direction.x = - (c->getComponent<TransformComponent>().position.x+30 - transform->position.x+20);
                    direction.y = - (c->getComponent<TransformComponent>().position.y+30 - transform->position.y+20);
                    direction.Normalize();
                    
               }
               //if goal in upper part
               if(c->getComponent<ColliderComponent>().tag == "upHitbox")
               {
                   audioGoal.play();
                   Game::score.x += 1;
                   direction = {0,0};
                   transform->position.x = 300;
                   transform->position.y = 459;
                   
               }
               //if goal in bottom part
               if(c->getComponent<ColliderComponent>().tag == "downHitbox")
               {
                   audioGoal.play();
                   Game::score.y += 1;
                   direction = {0,0};
                   transform->position.x = 300;
                   transform->position.y = 459;
                   
               }
           }
        }
        //apply direction
        transform->speed = speed;
        transform->velocity.x = direction.x;
        transform->velocity.y = direction.y;
        
    }

};

#endif