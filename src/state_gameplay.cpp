#include "state_gameplay.h"

void GameplayState::setup()
{
    winString = "YOU WIN!!! :D";
    loseString = "NEEEEEJ YOU LOST";
}

bool GameplayState::randomiseFirstMove()
{
    if ((rand() % 100) < 50)
        return true;
    else
        return false;
}

void GameplayState::takeMove()
{
    //display: "Your turn. Move a ghost."

    //event loop :O
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
                std::cout << "YEAH\n";
                processMoveInfo();
            }
        }
        else if (event.type == windbreeze::Event::MOUSEBUTTONPRESSED)
        {
            if (event.mouseButton.button == windbreeze::Mouse::LEFT)
            {
                mouseClickLeft(event.mouseButton.x, event.mouseButton.y);
                std::cout << "selected ghost at " << selectedX << " and " << selectedY << "\n";
                std::cout << "suggested ghost at " << suggestedX << " and " << suggestedY << "\n";
            }
        }
    }

}

bool GameplayState::checkIfValidMove()
{
    return suggested;
}

void GameplayState::waitForMove()
{
}

void GameplayState::setTileAsSelected(int x, int y)
{
    selected = true;
    selectedX = x;
    selectedY = y;
    selectedTile = tileGrid[y][x];
    renderer.setSelectedTile(x, y);
}

void GameplayState::setTileAsSuggested(int x, int y)
{
    suggested = true;
    suggestedX = x;
    suggestedY = y;
    suggestedTile = tileGrid[y][x];
    renderer.setSuggestedTile(x, y);
}

void GameplayState::deselectTile()
{
    selected = false;
    selectedX = -1;
    selectedY = -1;
    selectedTile.ghostState = NONE;
    selectedTile.playerState = NEITHER;
    renderer.setSelectedTile(-1, -1);
}

void GameplayState::desuggestTile()
{
    suggested = false;
    suggestedX = -1;
    suggestedY = -1;
    suggestedTile.ghostState = NONE;
    suggestedTile.playerState = NEITHER;
    renderer.setSuggestedTile(-1, -1);
}

bool GameplayState::surroundingSelectedTile(int x, int y)
{
    return (((x == selectedX + 1 || x == selectedX - 1) && y == selectedY)
        || ((y == selectedY + 1 || y == selectedY - 1) && x == selectedX));
}

void GameplayState::processMoveInfo()
{
    if (suggestedTile.ghostState == GOOD)
    {
        enemyGoodCaptured++;
        std::cout << "yay you captured a good enemy! good antal: " << enemyGoodCaptured << "\n";
    }
    else if (suggestedTile.ghostState == BAD)
    {
        enemyBadCaptured++;
        std::cout << "NEEEEEEEEJ you captured a bad enemy! bad antal: " << enemyBadCaptured << "\n";
        std::cout << "BLARGH suggested ghost at: " << suggestedX << " and " << suggestedY << "\n";
        std::cout << "and suggestedTile.ghostState: " << suggestedTile.ghostState << " and suggestedTile.playerState: " << suggestedTile.playerState << "\n";
    }
    std::cout << "HEJ\n";
    suggestedTile = selectedTile; //may result in questionable behaviour? :O - shouldn't
    selectedTile.playerState = NEITHER;
    std::cout << "HEJ\n";
    selectedTile.ghostState = NONE;
    desuggestTile();
    deselectTile();
}

void GameplayState::checkForGameOver()
{
}

bool GameplayState::withinGrid(int x, int y)
{
    return ((x <= 5 && x >= 0) && (y <= 5 && y >= 0));
}

void GameplayState::mouseClickLeft(int xPos, int yPos)
{
    int tileSize = renderer.getTileSize();
    int xTile = xPos/tileSize;
    int yTile = yPos/tileSize;

    if (withinGrid(xTile, yTile))
    {
        Tile& clickedTile = tileGrid[yTile][xTile];
        if (selected)
        {
            if (clickedTile.playerState == ONE)
            {
                setTileAsSelected(xTile, yTile);
                desuggestTile();
            }
            else if (surroundingSelectedTile(xTile, yTile))
            {
                setTileAsSuggested(xTile, yTile);
                //deselectTile();
            }
        }
        else
        {
            if (clickedTile.playerState == ONE)
            {
                setTileAsSelected(xTile, yTile);
                desuggestTile();
            }
        }
    }
}

std::string GameplayState::run()
{
    /*
    if (host)
    {
        turn = randomiseFirstMove();
        //send.TURNinfo();
    }
    //else
        //waitForFirstMoveSignal();
    
    if (turn)
        takeMove();
    else
        waitForMove();
    */

    takeMove();
    if (enemyGoodCaptured == 4)
    {
        renderer.renderText(sfWindow, winString);
    }
    else if (enemyBadCaptured == 4)
    {
        renderer.renderText(sfWindow, loseString);
    }
    else
    {
        renderer.render(sfWindow, tileGrid);
    }
    return nextState;
}
