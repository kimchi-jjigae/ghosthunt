#include "networker.h"

bool Networker::acceptConnection()
{
    // bind the listener to a port
    if (listener.listen(21212) != sf::Socket::Done)
    {
        std::cout << "it dint listn\n";
        return false;
    }
    else
        std::cout << "it  listn :O\n";

    // accept a new connection
    if (listener.accept(client) != sf::Socket::Done)
    {
        std::cout << "it dint accept client\n";
        return false;
    }
    else
        std::cout << "accepted!\n";
        return true;
}

bool Networker::connectToHost()
{
    sf::Socket::Status status = socket.connect("192.168.1.60", 21212);
    if (status != sf::Socket::Done)
    {
        std::cout << "Could not connect :(\n";
        return false;
    }
    else
        std::cout << "YEA CONNECTED MAYBE\n";
        return true;
}

bool Networker::receiveData()
{
    if (client.receive(data, 32, received) != sf::Socket::Done)
    {
        std::cout << "Received nothin\n";
        return false;
    }
    else
    {
        std::cout << "Received " << received << " bytes\n";
        std::cout << "it says: " << data << "\n";
        return true;
    }
}

bool Networker::sendData()
{
    if (socket.send(&kalle, 32) != sf::Socket::Done)
    {
        std::cout << "coulnt send\n";
        return false;
    }
    else
        std::cout << "mebbe sent\n";
        return true;
}
