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
        grid.placeEnemyGhosts(clientGhosts);
    }
    else
    {
        grid.placeEnemyGhosts(hostGhosts);
    }
    nextState = "gameplay";
    return nextState;
}

void SetupState::listenForSignal()
{
    std::cout << "listening for a signal!\n";
    if (networker.isHost())
    {
        networker.receiveData(listenPacket);
        listenPacket >> clientGhosts;
    }
    else
    {
        networker.receiveData(listenPacket);
        listenPacket >> hostGhosts;
    }

}

void SetupState::setupGhosts()
{
    std::cout << "setting up ghosts!\n";
    std::string s;
    if (networker.isHost())
    {
        s = "GGBBBBGG";
    }
    else
    {
        s = "GBGBBBGG";
    }
    setupPacket << s;
    networker.sendData(setupPacket);
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
