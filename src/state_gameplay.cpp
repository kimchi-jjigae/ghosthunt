#include "state_gameplay.h"
#include "state_setup.h"

void GameplayState::handOver(std::weak_ptr<GameState> previousState, std::string previousStateName)
{
    if (previousStateName == "setup")
    {
        std::weak_ptr<SetupState> setupState = std::static_pointer_cast<SetupState, GameState> (previousState.lock());
        turn = setupState.lock()->isTurn();
    }
}

void GameplayState::setup()
{
    winString = "YOU WIN!!! :D";
    loseString = "NEEEEEJ YOU LOST";
}

std::string GameplayState::run()
{
    nextState = "";

    if (turn)
    {
        turn = takeMove();

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
            renderer.render(sfWindow, grid);
        }
    }
    else if (!turn)
    {
        turn = waitForMove();

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
            renderer.render(sfWindow, grid);
        }
    }
    return nextState;
}

bool GameplayState::takeMove()
{
    //display: "Your turn. Move a ghost."
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
                return false;
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
    return true;
}

bool GameplayState::waitForMove()
{
    std::cout << "HAHA YOU CAN'T DO ANYTHING\n";
    sleep(2);
    return !turn;
}

void GameplayState::processMoveInfo()
{
    if (grid.isSuggested())
    {
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
