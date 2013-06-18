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
    grid.placeEnemyGhosts(enemyGhosts);
    nextState = "gameplay";
    return nextState;
}

void SetupState::listenForSignal()
{
    std::cout << "listening for a signal!\n";
    networker.receiveData(listenPacket);
    listenPacket >> enemyGhosts;
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
                    if (grid.checkIfSetupValid())
                    {
                        notSetUp = false;
                        setupPacket = grid.convertPositionsToPacket();
                        std::cout << "Klart! Ghosts set up!\n";
                    }
                    else
                    {
                        std::cout << "setup wasn't valid\n";
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
        //renderer.renderSetup(sfWindow, grid, host, int mousePosX, int mousePosY);
        renderer.render(sfWindow, grid, host);
    }
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
