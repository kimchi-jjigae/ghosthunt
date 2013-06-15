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

    if (connected)
    {
        std::cout << "IT DEFO IS CONNECTED\n";
        sf::Packet packet;
        if (networker.isHost())
        {
            sleep(3);

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
    else
        std::cout << "not connected :/\n";

}

std::string MenuState::run()
{
    if (connected)
    {
        std::cout << "Switching from menu to setup\n";
        nextState = "setup";
    }
    else
    {
        nextState = "";
    }
    return nextState;
}
