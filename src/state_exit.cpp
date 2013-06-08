#include "state_exit.h"

void ExitState::setup()
{
    
    textString = "Are you sure? Y or N";
}

std::string ExitState::run()
{
    windbreeze::Event event;
    std::string nextState;

    inputHandler.processEvents();
    while (inputHandler.pollEvent(event))
    {
        if (event.type == windbreeze::Event::KEYPRESSED)
        {
            if (event.key.code == windbreeze::Keyboard::Y)
            {
                nextState = "NONE";
            }
            if (event.key.code == windbreeze::Keyboard::N)
            {
                nextState = "gameplay";
            }
        }
    }
    renderer.renderText(sfWindow, textString);
    return nextState;
}
