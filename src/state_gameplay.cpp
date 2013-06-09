#include "state_gameplay.h"

void GameplayState::setup()
{
    winString = "YOU WIN!!! :D";
    loseString = "NEEEEEJ YOU LOST";
}

void GameplayState::setTileAsSelected(int x, int y)
{
    selected = true;
    selectedX = x;
    selectedY = y;
    selectedTile = tileGrid[y][x];
    renderer.setSelectedTile(x, y);
}

void GameplayState::deselectTile()
{
    selected = false;
    renderer.setSelectedTile(-1, -1);
}

bool GameplayState::surroundingSelectedTile(int x, int y)
{
    return (((x == selectedX + 1 || x == selectedX - 1) && y == selectedY)
        || ((y == selectedY + 1 || y == selectedY - 1) && x == selectedX));
}

void GameplayState::moveGhostTo(Tile& tile)
{
    if (tile.ghostState == GOOD)
    {
        enemyGoodCaptured++;
        std::cout << "yay you captured a good enemy! good antal: " << enemyGoodCaptured << "\n";
    }
    else if (tile.ghostState == BAD)
    {
        enemyBadCaptured++;
        std::cout << "NEEEEEEEEJ you captured a bad enemy! bad antal: " << enemyBadCaptured << "\n";
    }
    tile = selectedTile;
    tileGrid[selectedY][selectedX].playerState = NEITHER;
    tileGrid[selectedY][selectedX].ghostState = NONE;
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
            }
            else if (surroundingSelectedTile(xTile, yTile))
            {
                moveGhostTo(clickedTile);
                deselectTile();
            }
        }
        else
        {
            if (clickedTile.playerState == ONE)
            {
                setTileAsSelected(xTile, yTile);
            }
        }
    }
}

std::string GameplayState::run()
{
    windbreeze::Event event;
    std::string nextState;

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
        }
        else if (event.type == windbreeze::Event::MOUSEBUTTONPRESSED)
        {
            if (event.mouseButton.button == windbreeze::Mouse::LEFT)
            {
                mouseClickLeft(event.mouseButton.x, event.mouseButton.y);
            }
        }
    }

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
