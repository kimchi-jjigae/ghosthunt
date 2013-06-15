#include "state_menu.h"

void MenuState::setup()
{
    if (host)
    {
        networker.acceptConnection();
        turn = randomiseFirstMove();
    }
    else
    {
        networker.connectToHost();
    }
    //and then send more info here

}

void MenuState::setup()
{
}

std::string MenuState::run()
{
    nextState = "gameplay";
    return nextState;
}
