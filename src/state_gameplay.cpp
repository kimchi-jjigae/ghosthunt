#include "state_gameplay.h"

void GameplayState::setup()
{
}

std::string GameplayState::run()
{
    windbreeze::Event event;
    std::string nextState;

    inputHandler.processEvents();
    while (inputHandler.pollEvent(event))
    {
        if (event.type == windbreeze::Event::CLOSED)
        {
            nextState = "exit";
        }
        else if (event.type == windbreeze::Event::KEYPRESSED)
        {
            if (event.key.code == windbreeze::Keyboard::Q || event.key.code == windbreeze::Keyboard::ESCAPE)
            {
                nextState = "exit";
            }
        }
    }
    renderer.render(sfWindow, tileGrid);
    return nextState;
}
