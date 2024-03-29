#ifndef SPRITECOMPONENT_HPP_INCLUDED
#define SPRITECOMPONENT_HPP_INCLUDED

#include "Components.hpp"
#include "SDL2/SDL.h"
#include "../TextureManager.hpp"
#include "Animation.hpp"
#include <map>
#include <cstring>

//component draws sprite (animated or not)

class SpriteComponent : public Component
{
private:
    TransformComponent *transform = nullptr;
    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;
    
    
    bool animated = false;
    int frames = 0;
    int speed = 100;
    
public:
    
    int animIndex = 1;
    
    struct StringCompare
    {
        bool operator()(const char *a, const char *b)
        {
            return std::strcmp(a, b) < 0;
        }
    };
        
        
    std::map<const char*, Animation, StringCompare> animations;
    
    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
    
    
    SpriteComponent() = default;

    SpriteComponent(const char* path)
    {
        setTex(path);
    }
    
    SpriteComponent(const char* path, bool isAnimated)
    {
        animated = isAnimated;
        
        
        Animation glow = Animation(0, 12, 50);
        Animation idle = Animation(1, 1, 200);
    
        animations.emplace("glow", glow);
        animations.emplace("idle", idle);
    
        Play("glow");
        
        
        
        setTex(path);
    }
    
    
    
    ~SpriteComponent()
    {
        SDL_DestroyTexture(texture);
    }

    void setTex(const char* path)
    {
        texture = TextureManager::LoadTexture(path);
    }

    void init() override
    {
        if(entity->hasComponent<TransformComponent>())
            transform = &entity->getComponent<TransformComponent>();
        
        srcRect.x = srcRect.y = 0;
        srcRect.w = transform->width;
        srcRect.h = transform->height;



    }

    void update() override
    {
        if(animated)
        {
            srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
            srcRect.y = animIndex * transform->height;
        }

        destRect.x = static_cast<int>(transform->position.x);
        destRect.y = static_cast<int>(transform->position.y);
        
        destRect.w = transform->width * transform->scale;
        destRect.h = transform->height * transform->scale;
        
    }

    void draw() override
    {
        TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
    }


    void Play(const char* animName)
    {
        frames = animations[animName].frames;
        animIndex = animations[animName].index;
        speed = animations[animName].speed;
    }

};

#endif // SPRITECOMPONENT_HPP_INCLUDED
