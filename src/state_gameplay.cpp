#include "state_gameplay.h"
#include "state_setup.h"

void GameplayState::activate(std::string previousState)
{
    nextState = "";
    std::cout << "\n\n ---GAMEPLAY BEGINS NOW--- \n\n";
    host = networker.isHost();
    if (host)
    {
        turn = randomiseFirstMove();
        packet << turn;
        networker.sendData(packet);
    }
    else
    {
        networker.receiveData(packet);
        packet >> turn;
        turn = !turn;
    }
    winString = "YOU WIN!!! :D";
    loseString = "NEEEEEJ YOU LOST";
}

std::string GameplayState::run()
{
    if (!turn && !waiting)
    {
        //display: "Waiting for the other player"
        std::cout << "Waiting for the other player\n";
        waitThread = std::thread(&GameplayState::waitForTurn, this);
        waiting = true;
    }
    else if (turn)
    {
        //display: "Your turn. Move a ghost."
        //std::cout << "Your turn. Move a ghost.\n";
    }
    eventLoop();
    bregott();
    return nextState;
}

//
void GameplayState::waitForTurn()
{
    int a, b, c, d;
    std::string s;
    networker.receiveData(packet);
    grid.placeMove(packet);
    turn = true;
    waiting = false;
    checkForGameOver();
    waitThread.detach();
}

void GameplayState::eventLoop()
{
    windbreeze::Event event;
    inputHandler.processEvents();
    while (inputHandler.pollEvent(event))
    {
        if (event.type == windbreeze::Event::CLOSED)
        {
            nextState = "exit";
        }
        else if (event.type == windbreeze::Event::KEYPRESSED)
        {
            if (event.key.code == windbreeze::Keyboard::Q || event.key.code == windbreeze::Keyboard::ESCAPE)
            {
                nextState = "exit";
            }
            if (event.key.code == windbreeze::Keyboard::M)
            {
                if (turn)
                {
                    processMoveInfo();
                }
            }
        }
        else if (event.type == windbreeze::Event::MOUSEBUTTONPRESSED)
        {
            if (event.mouseButton.button == windbreeze::Mouse::LEFT)
            {
                mouseClickLeft(event.mouseButton.x, event.mouseButton.y);
                std::cout << "selected ghost at " << grid.getSelectedCoords().x << " and " << grid.getSelectedCoords().y << "\n";
                std::cout << "suggested ghost at " << grid.getSuggestedCoords().x << " and " << grid.getSuggestedCoords().y << "\n";
            }
        }
    }
}

void GameplayState::processMoveInfo()
{
    if (grid.isSuggested())
    {
        packet = grid.convertMoveToPacket();
        networker.sendData(packet);
        if (grid.getSuggestedTile().ghostState == GOOD) 
        {
            grid.p2GoodGhostAmount--;
            std::cout << "yay you captured a good enemy! good antal kvar: " << grid.p2GoodGhostAmount << "\n";
        }
        else if (grid.getSuggestedTile().ghostState == BAD) 
        {
            grid.p2BadGhostAmount--;
            std::cout << "NEEEEEEEEJ you captured a bad enemy! bad antal kvar: " << grid.p2BadGhostAmount << "\n";
        }
        grid.moveSelectToSuggest();
        checkForGameOver();
        turn = false;
    }
    else
        std::cout << "No move suggested.\n";
}

void GameplayState::mouseClickLeft(int xPos, int yPos)
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
                grid.setSelectedTile(xTile, yTile);
                grid.desuggestTile();
            }
            else if (grid.surroundingSelectedTile(xTile, yTile))
            {
                grid.setSuggestedTile(xTile, yTile);
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

bool GameplayState::randomiseFirstMove()
{
    if ((rand() % 100) < 50)
        return true;
    else
        return false;
}

void GameplayState::checkForGameOver()
{
    if (grid.p1GoodGhostAmount == 0)
    {
        gameOver = 2;
    }
    else if (grid.p1BadGhostAmount == 0)
    {
        gameOver = 1;
    }
    else if (grid.p2GoodGhostAmount == 0)
    {
        gameOver = 1;
    }
    else if (grid.p2BadGhostAmount == 0)
    {
        gameOver = 2;
    }
    else
    {
        gameOver = 0;
    }
}

void GameplayState::bregott()
{
    switch (gameOver) {
    case 0: 
        renderer.render(sfWindow, grid, host);
        break;
    case 1: 
        renderer.renderText(sfWindow, winString);
        break;
    case 2: 
        renderer.renderText(sfWindow, loseString);
        break;
    }
}
