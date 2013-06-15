#include "ghosthunt.h"
#include "state_menu.h"
#include "state_gameplay.h"
#include "state_exit.h"

void GhostHunt::setup()
{
    window.create(windbreeze::VideoMode(600, 600), "GHOST HUNT");
    window.setFramerateLimit(60);

    stateMachine.addGameState("menu", std::shared_ptr<MenuState>(new MenuState(sfWindow, inputHandler, actionHandler, networker, renderer)));
    stateMachine.addGameState("gameplay", std::shared_ptr<GameplayState>(new GameplayState(sfWindow, inputHandler, actionHandler, networker, renderer)));
    stateMachine.addGameState("exit", std::shared_ptr<ExitState>(new ExitState(sfWindow, inputHandler, renderer)));
    stateMachine.setCurrentState("menu");
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
