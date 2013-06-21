#include "state_setup.h"

void SetupState::activate(std::string previousState)
{
    host = networker.isHost();
    nextState = "";
}

std::string SetupState::run()
{
    if (!waiting)
    {
        listenThread = std::thread(&SetupState::listenForSignal, this);
        waiting = true;
    }
    eventLoop();

    if (received && sentSetup)
    {
        nextState = "gameplay";
    }
    else
    {
        nextState = "";
    }

    int mouseX = sf::Mouse::getPosition().x;
    int mouseY = sf::Mouse::getPosition().y;
    renderer.renderSetup(grid, host, mouseX, mouseY);

    return nextState;
}

void SetupState::listenForSignal()
{
    std::cout << "listening for a signal!\n";
    networker.receiveData(listenPacket);
    listenPacket >> enemyGhosts;
    grid.placeEnemyGhosts(enemyGhosts);
    received = true;
}

void SetupState::eventLoop()
{
    windbreeze::Event event;
    inputHandler.processEvents();
    while (inputHandler.pollEvent(event))
    {
        if (event.type == windbreeze::Event::CLOSED)
        {
            nextState = "exit";
        }
        if (event.type == windbreeze::Event::KEYPRESSED)
        {
            if (event.key.code == windbreeze::Keyboard::Q || event.key.code == windbreeze::Keyboard::ESCAPE)
            {
                nextState = "exit";
            }
            if (event.key.code == windbreeze::Keyboard::K)
            {
                if (!sentSetup)
                {
                    if (grid.checkIfSetupValid())
                    {
                        std::cout << "Klart! Sending ghosts!\n";
                        setupPacket = grid.convertPositionsToPacket();
                        networker.sendData(setupPacket);
                        sentSetup = true;
                    }
                    else
                    {
                        std::cout << "Setup wasn't valid\n";
                    }
                }
                else
                {
                    std::cout << "You've already set stuff up.\n";
                }
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
