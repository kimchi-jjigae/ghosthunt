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

                std::cout << "tile x: " << xTile << ", ";
                std::cout << "tile y: " << yTile << "\n";

                Tile& selectedTile = tileGrid[yTile][xTile];
                renderer.setSelectedTile(xTile, yTile);
            }
        }
    }
    renderer.render(sfWindow, tileGrid);
    return nextState;
}
