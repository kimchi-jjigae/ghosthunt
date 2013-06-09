#include "state_gameplay.h"

void GameplayState::setup()
{
    winString = "YOU WIN!!! :D";
    loseString = "NEEEEEJ YOU LOST";
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

                //std::cout << "tile x: " << xTile << ", ";
                //std::cout << "tile y: " << yTile << "\n";

                //make sure it is within bounds
                if ((xTile <= 5 && xTile >= 0) && (yTile <= 5 && yTile >= 0))
                {
                    Tile& clickedTile = tileGrid[yTile][xTile];
                    if (selected)
                    {
                        std::cout << "hej\n";
                        if (clickedTile.playerState == ONE)
                        {
                            renderer.setSelectedTile(xTile, yTile);
                            selected = true;
                            selectedX = xTile;
                            selectedY = yTile;
                            selectedTile = tileGrid[selectedY][selectedX];
                        }
                        else if (((xTile == selectedX + 1 || xTile == selectedX - 1) && yTile == selectedY)
                              || ((yTile == selectedY + 1 || yTile == selectedY - 1) && xTile == selectedX))
                        {
                            std::cout << "YEAH\n";
                            // have an if for winning (check if good ghost and select exit) - later
                            // if empty tile
                            // if ghost of others
                            if (clickedTile.ghostState == GOOD)
                            {
                                enemyGoodCaptured++;
                                std::cout << "yay you captured a good enemy! good antal: " << enemyGoodCaptured << "\n";
                            }
                            else if (clickedTile.ghostState == BAD)
                            {
                                enemyBadCaptured++;
                                std::cout << "NEEEEEEEEJ you captured a bad enemy! bad antal: " << enemyBadCaptured << "\n";
                            }
                            clickedTile = selectedTile;
                            tileGrid[selectedY][selectedX].playerState = NEITHER;
                            tileGrid[selectedY][selectedX].ghostState = NONE;
                            renderer.setSelectedTile(-1, -1);
                        }
                    }
                    else
                    {
                        if (clickedTile.playerState == ONE)
                        {
                            renderer.setSelectedTile(xTile, yTile);
                            selected = true;
                            selectedX = xTile;
                            selectedY = yTile;
                            selectedTile = tileGrid[selectedY][selectedX];
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
