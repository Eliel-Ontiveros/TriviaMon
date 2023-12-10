#pragma once
#include "Game.h"
#include "ECS/Components.h"
#include "SDL.h"

class ClickableComponent : public Component
{
public:
    typedef void (*ClickFunction)();

    ClickableComponent(ClickFunction onClick) : onClick(onClick) {}


private:
    ClickFunction onClick;
};
