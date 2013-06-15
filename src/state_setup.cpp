#include "state_setup.h"

void SetupState::setup()
{
    sf::Packet packet;
    if (networker.isHost())
    {
        turn = randomiseFirstMove();

        // on sending side
        uint16_t x = 10;
        std::string s = "hello";
        double d = 0.6;

        packet << x << s << d;
        networker.sendData(packet);
    }
    else
    {
        networker.receiveData(packet);
        // on receiving side
        uint16_t y;
        std::string t;
        double e;
        packet >> y >> t >> e;
        std::cout << "it is " << y << " and " << t << " and " << e << "\n";
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
    if ((rand() % 100) < 50)
        return true;
    else
        return false;
}

bool SetupState::isTurn()
{
    return turn;
}
