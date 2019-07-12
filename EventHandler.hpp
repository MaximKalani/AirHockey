#ifndef EVENTHANDLER_HPP_INCLUDED
#define EVENTHANDLER_HPP_INCLUDED

#include "engine.hpp"
#include "ECS/ECS.hpp"
#include "ECS/Components.hpp"


class EventHandler
{
public:
    TransformComponent *transform;
    void handleInput(Entity* player);
    
};

#endif