#pragma once
#include <SFML/Network.hpp>
#include <iostream>

class Networker
{
    public:
        Networker();
        bool acceptConnection();
        bool connectToHost();
        bool receiveData();
        bool sendData();

        int getPortNumber();
        bool isHost();

    private:
        std::string hostAddress = "127.0.0.1";
        int portNumber = 21212;

        sf::TcpListener listener; 
        sf::TcpSocket client;
        sf::TcpSocket socket;

        char data[32];
        std::size_t received;
        char kalle[32] = {'j', 'a', 'g', ' ', 'g', 'i', 'l', 'l', 'a', 'r', ' ', 'd', 'i', 'g', ' ', 'm', 'i', 'n', ' ', 'd', 'i', 'n', 'o', 's', 'a', 'u', 'r', 'i', 'e'}; 

        bool host = true;
};
