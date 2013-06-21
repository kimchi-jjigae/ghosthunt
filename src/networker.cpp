#include "networker.h"

Networker::Networker()
{}

bool Networker::acceptConnection()
{
    // bind the listener to a port
    std::cout << "Listening on port " << portNumber << "... " << std::flush;
    if (listener.listen(portNumber) != sf::Socket::Done)
    {
        std::cout << "Port cannot be opened.\n";
        return false;
    }
    else
        std::cout << "Port successfully opened!\n";

    // accept a new connection
    std::cout << "Waiting for the other player to connect... " << std::flush;
    if (listener.accept(socket) != sf::Socket::Done)
    {
        std::cout << "The other play could not connect.\n";
        return false;
    }
    else
    {
        std::cout << "The other player is connected!\n";
        return true;
    }
}

bool Networker::connectToHost()
{
    sf::Socket::Status status = socket.connect(hostAddress, portNumber);
    std::cout << "Connecting to port " << portNumber << " on " << hostAddress << "... " << std::flush;
    if (status != sf::Socket::Done)
    {
        std::cout << "Could not connect to the host.\n";
        return false;
    }
    else
    {
        std::cout << "Connection successfully established!\n";
        return true;
    }
}

bool Networker::receiveData(sf::Packet& packet)
{
    std::cout << "Waiting to receive data... " << std::flush;
    if (socket.receive(packet) != sf::Socket::Done)
    {
        std::cout << "Failed to receive anything.\n";   // make it disconnect? :O
        return false;
    }
    else
    {
        std::cout << "Received!\n";
        return true;
    }
}

bool Networker::sendData(sf::Packet& packet)
{
    std::cout << "Sending data... " << std::flush;
    if (socket.send(packet) != sf::Socket::Done)
    {
        std::cout << "Data could not be sent.\n";
        return false;
    }
    else
    {
        std::cout << "Sent!\n";
        return true;
    }
}

int Networker::getPortNumber()
{
    return portNumber;
}

bool Networker::isHost()
{
    return host;
}
