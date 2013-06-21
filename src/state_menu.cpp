#include "state_menu.h"

void MenuState::setup()
{
    if (networker.isHost())
    {
        connected = networker.acceptConnection();
    }
    else
    {
        connected = networker.connectToHost();
    }

    sfWindow.resetGLStates();

}

std::string MenuState::run()
{
    windbreeze::Event event;
    inputHandler.processEvents();
    while (inputHandler.pollEvent(event))
    {
        clicky.desktop.HandleEvent((sf::Event)event);   // gotta convert this! :) 
        if (event.type == windbreeze::Event::CLOSED)
        {
            nextState = "exit";
        }
        if (event.type == windbreeze::Event::KEYPRESSED)
        {
            if (event.key.code == windbreeze::Keyboard::Q || event.key.code == windbreeze::Keyboard::ESCAPE)
            {
                nextState = "exit";
            }
        }
    }

    clicky.desktop.Update(clock.restart().asSeconds());

    //render
    sfWindow.clear();
    clicky.sfgui.Display(sfWindow);
    sfWindow.display();
    
    if (connected)
    {
        std::cout << "Switching from menu to setup\n";
        nextState = "setup";
    }
    else
    {
        nextState = "setup"; // change this to ""
    }
    return nextState;
}

void MenuState::haxEventConversion();
