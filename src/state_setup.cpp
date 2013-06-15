#include "state_setup.h"

void SetupState::setup()
{
    if (networker.isHost())
    {
        turn = randomiseFirstMove();
    }

}

std::string SetupState::run()
{
    std::cout << "bajs\n";
    nextState = "gameplay";
    return nextState;
}

bool SetupState::randomiseFirstMove()
{
    if ((rand() % 100) < 99)
        return true;
    else
        return false;
}

bool SetupState::isTurn()
{
    return turn;
}
