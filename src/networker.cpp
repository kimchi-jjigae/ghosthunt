#include "networker.h"

Networker::Networker()
{}

bool Networker::acceptConnection()
{
    // bind the listener to a port
    std::cout << "Listening on port " << portNumber << "... " << std::flush;
    if (listener.listen(portNumber) != sf::Socket::Done)
    {
        std::cout << "it dint listn\n";
        return false;
    }
    else
        std::cout << "it  listn :O\n";

    // accept a new connection
    std::cout << "Waiting for the other player to connect... " << std::flush;
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
    std::cout << "Connecting to port " << portNumber << " on " << hostAddress << "... " << std::flush;
    if (status != sf::Socket::Done)
    {
        std::cout << "Could not connect :(\n";
        return false;
    }
    else
        std::cout << "YEA CONNECTED MAYBE\n";
        return true;
}

bool Networker::receiveData(sf::Packet& packet)
{
    std::cout << "Waiting to receive data... " << std::flush;
    if (client.receive(packet) != sf::Socket::Done)
    {
        std::cout << "Received nothin\n";
        return false;
    }
    else
    {
        std::cout << "Possibly received somethin\n";
        return true;
    }
}

bool Networker::sendData(sf::Packet& packet)
{
    std::cout << "Sending data... " << std::flush;
    if (socket.send(packet) != sf::Socket::Done)
    {
        std::cout << "coulnt send\n";
        return false;
    }
    else
    {
        std::cout << "mebbe sent\n";
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
