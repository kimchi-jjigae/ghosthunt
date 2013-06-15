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
            renderer.render(sfWindow, tileGrid);
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
            renderer.render(sfWindow, tileGrid);
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
                std::cout << "selected ghost at " << selectedX << " and " << selectedY << "\n";
                std::cout << "suggested ghost at " << suggestedX << " and " << suggestedY << "\n";
            }
        }
    }
    return true;
}

bool GameplayState::checkIfValidMove()
{
    return suggested;
}

bool GameplayState::waitForMove()
{
    std::cout << "HAHA YOU CAN'T DO ANYTHING\n";
    sleep(2);
    return !turn;
}

void GameplayState::setTileAsSelected(int x, int y)
{
    selected = true;
    selectedX = x;
    selectedY = y;
    renderer.setSelectedTile(x, y);
}

void GameplayState::setTileAsSuggested(int x, int y)
{
    suggested = true;
    suggestedX = x;
    suggestedY = y;
    renderer.setSuggestedTile(x, y);
}

void GameplayState::deselectTile()
{
    selected = false;
    selectedX = -1;
    selectedY = -1;
    renderer.setSelectedTile(-1, -1);
}

void GameplayState::desuggestTile()
{
    suggested = false;
    suggestedX = -1;
    suggestedY = -1;
    renderer.setSuggestedTile(-1, -1);
}

bool GameplayState::surroundingSelectedTile(int x, int y)
{
    return (((x == selectedX + 1 || x == selectedX - 1) && y == selectedY)
        || ((y == selectedY + 1 || y == selectedY - 1) && x == selectedX));
}

void GameplayState::processMoveInfo()
{
    if (suggested)
    {
        if (tileGrid.at(suggestedY).at(suggestedX).ghostState == GOOD)
        {
            enemyGoodCaptured++;
            std::cout << "yay you captured a good enemy! good antal: " << enemyGoodCaptured << "\n";
        }
        else if (tileGrid.at(suggestedY).at(suggestedX).ghostState == BAD)
        {
            enemyBadCaptured++;
            std::cout << "NEEEEEEEEJ you captured a bad enemy! bad antal: " << enemyBadCaptured << "\n";
        }
        tileGrid.at(suggestedY).at(suggestedX) = tileGrid.at(selectedY).at(selectedX);
        tileGrid.at(selectedY).at(selectedX).playerState = NEITHER;
        tileGrid.at(selectedY).at(selectedX).ghostState = NONE;
        desuggestTile();
        deselectTile();
    }
    else
        std::cout << "No move suggested.\n";
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
        Tile& clickedTile = tileGrid.at(yTile).at(xTile);
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
