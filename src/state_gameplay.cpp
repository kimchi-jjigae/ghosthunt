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
        std::cout << "I AM HOST AND SENDING TURN DATA. Turn is: " << turn << "\n";
        packet << turn;
        networker.sendData(packet);
    }
    else
    {
        networker.receiveData(packet);
        packet >> turn;
        std::cout << "I am not host. I received turn as: " << turn << " which I will now invert. \n";
        turn = !turn;
        std::cout << "I am not host but i received the turn data. Turn is: " << turn << "\n";
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
    else if (turn && !moveDone)
    {
        //display: "Your turn. Move a ghost."
        std::cout << "Your turn. Move a ghost.\n";
    }
    eventLoop();
    renderer.render(sfWindow, grid, host);
    return nextState;
}

void GameplayState::waitForTurn()
{
    int a, b, c, d;
    std::string s;
    waiting = true;
    networker.receiveData(packet);
    /*
    packet >> a >> b >> c >> d >> s;
    std::cout << "taking a packet that has " << a << " and " << b << " and " << c << " and " << d << " and " << s << "\n";
    */
    grid.placeMove(packet);
    turn = true;
    waiting = false;
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
                if (turn && !moveDone)
                {
                    std::cout << "YEAH\n";
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
            enemyGoodCaptured++;
            std::cout << "yay you captured a good enemy! good antal: " << enemyGoodCaptured << "\n";
        }
        else if (grid.getSuggestedTile().ghostState == BAD) 
        {
            enemyBadCaptured++;
            std::cout << "NEEEEEEEEJ you captured a bad enemy! bad antal: " << enemyBadCaptured << "\n";
        }
        grid.moveSelectToSuggest();
        moveDone = true;
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

