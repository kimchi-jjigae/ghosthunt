#include "state_setup.h"

void SetupState::activate(std::string previousState)
{
    turn = randomiseFirstMove();
}

std::string SetupState::run()
{
    std::thread listenThread(&SetupState::listenForSignal, this);
    std::thread setupGhostsThread(&SetupState::setupGhosts, this);
    listenThread.join();
    setupGhostsThread.join();
    if (networker.isHost())
    {
        grid.placeEnemyGhosts(enemyState);
    }
    nextState = "gameplay";
    return nextState;
}

void SetupState::listenForSignal()
{
    std::cout << "listening for a signal!\n";
    if (networker.isHost())
    {
        networker.receiveData(packet);
        packet >> enemyState;
    }
}

void SetupState::setupGhosts()
{
    if (!(networker.isHost()))
    {
        std::cout << "setting up ghosts!\n";
        sleep(1);
        std::string s = "GBGBBBGG";
        packet << s;
        networker.sendData(packet);
    }
}

bool SetupState::randomiseFirstMove()
{
    if ((rand() % 100) < 50)
        return true;
    else
        return false;
}

bool SetupState::isTurn()
{
    return turn;
}
