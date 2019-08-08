#pragma once

#include "Window.hpp"
#include "EventManager.hpp"
#include "StateMachine.hpp"

struct SharedContext {
    Window * window;
    StateMachine * stateMachine;
    EventManager * eventManager;
//    EntityManager * entityManager;
//    AssetManager * assetManager;
};
