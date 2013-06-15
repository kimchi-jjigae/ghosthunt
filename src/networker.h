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
        std::string hostAddress = "127.0.0.1";
        int portNumber = 21212;

        sf::TcpListener listener; 
        sf::TcpSocket client;
        sf::TcpSocket socket;

        bool host = true;
};
