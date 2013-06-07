#include "ghosthunt.h"
#include "state_gameplay.h"

void GhostHunt::setup()
{
    window.create(windbreeze::VideoMode(600, 600), "GHOST HUNT");
    window.setFramerateLimit(60);

    stateMachine.addGameState("gameplay", std::shared_ptr<GameplayState>(new GameplayState(sfWindow, inputHandler, actionHandler)));
    stateMachine.setCurrentState("gameplay");
}

void GhostHunt::destroy()
{
    window.close();
}

void GhostHunt::loop()
{
    stateMachine.run();

    if(stateMachine.isFinished())
        quit();
}
