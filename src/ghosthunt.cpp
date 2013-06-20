#include "ghosthunt.h"
#include "state_menu.h"
#include "state_setup.h"
#include "state_gameplay.h"
#include "state_exit.h"

void GhostHunt::setup()
{
    window.create(windbreeze::VideoMode(600, 600), "GHOST HUNT");
    window.setFramerateLimit(60);

    stateMachine.addGameState("menu", std::shared_ptr<MenuState>(new MenuState(sfWindow, inputHandler, actionHandler, networker, renderer, clicky)));
    stateMachine.addGameState("setup", std::shared_ptr<SetupState>(new SetupState(sfWindow, inputHandler, actionHandler, networker, renderer, grid)));
    stateMachine.addGameState("gameplay", std::shared_ptr<GameplayState>(new GameplayState(sfWindow, inputHandler, actionHandler, networker, renderer, grid)));
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
