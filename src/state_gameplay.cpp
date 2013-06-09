#include "state_gameplay.h"

void GameplayState::setup()
{
}

std::string GameplayState::run()
{
    windbreeze::Event event;
    std::string nextState;
    bool selected;

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
                int selectedX;
                int selectedY;

                std::cout << "tile x: " << xTile << ", ";
                std::cout << "tile y: " << yTile << "\n";

                Tile& clickedTile = tileGrid[yTile][xTile];
                
                if (selected)
                {
                    if (clickedTile.playerState == ONE)
                    {
                        renderer.setSelectedTile(xTile, yTile);
                        selected = true;
                        selectedX = xTile;
                        selectedY = yTile;
                        int bajs = selectedY + selectedX;
                    }
                    /*
                    else if ((xTile == selectedX + 1 || xTile == selectedX - 1)
                          && (yTile == selectedY + 1 || yTile == selectedY -1))
                    {
                        if (
                    }
                    */
                }
                else
                {
                    if (clickedTile.playerState == ONE)
                    {
                        renderer.setSelectedTile(xTile, yTile);
                        selected = true;
                        selectedX = xTile;
                        selectedY = yTile;
                    }
                }
                
            }
        }
    }
    renderer.render(sfWindow, tileGrid);
    return nextState;
}
