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
    inputHandler.processEvents();
    while (inputHandler.pollEvent(event))
    {
        desktop.HandleEvent((sf::Event)event);
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

    desktop.Update(clock.restart().asSeconds());

    //render
    sfWindow.clear();
    sfgui.Display(sfWindow);
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
