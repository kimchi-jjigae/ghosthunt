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


}

std::string MenuState::run()
{
    //std::cout << "again connected is: " << connected << "\n";
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
