#include "state_setup.h"

void SetupState::activate(std::string previousState)
{
    turn = randomiseFirstMove();
    host = networker.isHost();
}

std::string SetupState::run()
{
    std::thread listenThread(&SetupState::listenForSignal, this);
    std::thread setupGhostsThread(&SetupState::setupGhosts, this);
    listenThread.join();
    setupGhostsThread.join();
    if (host)
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
    if (host)
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
    bool notSetUp = true;
    while (notSetUp)
    {
        windbreeze::Event event;
        inputHandler.processEvents();
        while (inputHandler.pollEvent(event))
        {
            /*
            if (event.type == windbreeze::Event::CLOSED)
            {
                nextState = "exit";
            }
            */
            if (event.type == windbreeze::Event::KEYPRESSED)
            {
                /*
                if (event.key.code == windbreeze::Keyboard::Q || event.key.code == windbreeze::Keyboard::ESCAPE)
                {
                    nextState = "exit";
                }
                */
                if (event.key.code == windbreeze::Keyboard::K)
                {
                    std::cout << "Klart!\n";
                    // checkIfPiecesValid();
                    // convertPositionsToString();
                    notSetUp = false;
                }
            }
            else if (event.type == windbreeze::Event::MOUSEBUTTONPRESSED)
            {
                if (event.mouseButton.button == windbreeze::Mouse::LEFT)
                {
                    mouseClickLeft(event.mouseButton.x, event.mouseButton.y);
                }
            }
        }
        renderer.render(sfWindow, grid, host);
    }

    std::cout << "setting up ghosts!\n";
    std::string s;
    if (host)
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

void SetupState::mouseClickLeft(int xPos, int yPos)
{
    int tileSize = renderer.getTileSize();
    int xTile = xPos/tileSize;
    int yTile = yPos/tileSize;

    if (grid.withinGrid(xTile, yTile))
    {
        Tile clickedTile = grid.getTileAt(xTile, yTile);
        if (grid.isSelected())
        {
            if (clickedTile.playerState == ONE)
            {
                grid.setSuggestedTile(xTile, yTile);
                grid.swapSelectAndSuggest();
            }
            else if (clickedTile.playerState == NEITHER)
            {
                grid.setSuggestedTile(xTile, yTile);
                grid.swapSelectAndSuggest();
            }
            else
            {
                grid.deselectTile();
                grid.desuggestTile();
            }
        }
        else
        {
            if (clickedTile.playerState == ONE)
            {
                grid.setSelectedTile(xTile, yTile);
                grid.desuggestTile();
            }
        }
    }
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
