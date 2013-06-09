#include "state_gameplay.h"

void GameplayState::setup()
{
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
                            // have an if for winning (check if good ghost and select exit)
                            // if for checking boundary - but already checked for? :O
                            // if empty tile
                            // if ghost of others
                            // if ghost of self
                            tileGrid[yTile][xTile] = selectedTile;
                            tileGrid[selectedY][selectedX].playerState = NEITHER;
                            tileGrid[selectedY][selectedX].ghostState = NONE;
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
    renderer.render(sfWindow, tileGrid);
    return nextState;
}
