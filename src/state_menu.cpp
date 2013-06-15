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
    //and then send more info here

}

std::string MenuState::run()
{
    std::cout << "MENU YEYE\n";
    if (connected)
        nextState = "setup";
    else
        nextState = "";
    return nextState;
}
