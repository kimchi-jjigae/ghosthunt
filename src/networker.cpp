#include "networker.h"

Networker::Networker()
{}

bool Networker::acceptConnection()
{
    // bind the listener to a port
    std::cout << "Listening on port " << portNumber << "... ";
    if (listener.listen(portNumber) != sf::Socket::Done)
    {
        std::cout << "it dint listn\n";
        return false;
    }
    else
        std::cout << "it  listn :O\n";

    // accept a new connection
    std::cout << "Waiting for the other player to connect... ";
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
    sf::Socket::Status status = socket.connect(hostAddress, portNumber);
    std::cout << "Connecting to port " << portNumber << " on " << hostAddress << "... ";
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

int Networker::getPortNumber()
{
    return portNumber;
}

bool Networker::isHost()
{
    return host;
}
