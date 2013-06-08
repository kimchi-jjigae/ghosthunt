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
        else if (event.type == windbreeze::Event::MOUSEBUTTONPRESSED)
        {
            if (event.mouseButton.button == windbreeze::Mouse::LEFT)
            {
                int xPos = event.mouseButton.x;
                int yPos = event.mouseButton.y;
                std::cout << "int x: " << xPos << "\n";
                std::cout << "int y: " << yPos << "\n";
            }
        }
    }
    renderer.renderText(sfWindow, textString);
    return nextState;
}
