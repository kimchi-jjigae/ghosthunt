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
                int tileSize = renderer.getTileSize();
                int xTile = event.mouseButton.x/tileSize;
                int yTile = event.mouseButton.y/tileSize;

                if ((xTile <= 5 && xTile >= 0) && (yTile <= 5 && yTile >= 0))
                {
                    Tile& clickedTile = tileGrid[yTile][xTile];
                    if (selected)
                    {
                        // reselect another tile
                        if (clickedTile.playerState == ONE)
                        {
                            setTileAsSelected(xTile, yTile);
                        }
                        // check if selecting a surrounding tile
                        else if (((xTile == selectedX + 1 || xTile == selectedX - 1) && yTile == selectedY)
                              || ((yTile == selectedY + 1 || yTile == selectedY - 1) && xTile == selectedX))
                        {
                            // if clicked tile is a good enemy
                            if (clickedTile.ghostState == GOOD)
                            {
                                enemyGoodCaptured++;
                                std::cout << "yay you captured a good enemy! good antal: " << enemyGoodCaptured << "\n";
                            }
                            // if clicked tile is a bad enemy
                            else if (clickedTile.ghostState == BAD)
                            {
                                enemyBadCaptured++;
                                std::cout << "NEEEEEEEEJ you captured a bad enemy! bad antal: " << enemyBadCaptured << "\n";
                            }
                            clickedTile = selectedTile;
                            tileGrid[selectedY][selectedX].playerState = NEITHER;
                            tileGrid[selectedY][selectedX].ghostState = NONE;
                            renderer.setSelectedTile(-1, -1);
                            selected = false;
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
