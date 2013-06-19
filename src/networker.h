#pragma once
#include <SFML/Network.hpp>
#include <iostream>

class Networker
{
    public:
        Networker();
        bool acceptConnection();
        bool connectToHost();
        bool receiveData(sf::Packet& packet);
        bool sendData(sf::Packet& packet);

        int getPortNumber();
        bool isHost();

    private:
        std::string hostAddress = "192.168.1.60";
        int portNumber = 21212;

        sf::TcpListener listener; 
        sf::TcpSocket socket;

        bool host = false;
};
