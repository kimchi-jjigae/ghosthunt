#include <framework/application/gamestate.h>
#include <framework/input/inputhandler.h>
#include <framework/util/sfml/sfmlinputbackend.h>
#include <framework/input/actionhandler.h>
#include <framework/window/window.h>
#include <framework/util/sfml/sfmlwindowbackend.h>
#include <framework/application/gamestatemachine.h>
#include <SFML/Graphics.hpp>
#include "renderer.h"
#include <iostream>
#include <stdlib.h>

class GameplayState : public windstorm::GameState
{
    public:
        //virtual void activate(std::string previousState) {}
        //virtual void deactivate(std::string nextState) {}
        //virtual void handOver(std::weak_ptr<GameState> previousState, std::string previousStateName) {}
        GameplayState(sf::RenderWindow& sfw, windbreeze::InputHandler& ih, windbreeze::ActionHandler<std::string>& ah) : sfWindow(sfw), inputHandler(ih), actionHandler(ah) {}
        void setup() override;
        std::string run() override;
        //virtual void destroy() {}
        //virtual ~GameState() {}

    private:
        sf::RenderWindow& sfWindow;
        windbreeze::InputHandler& inputHandler;
        windbreeze::ActionHandler<std::string>& actionHandler;
        Renderer renderer;

        std::vector<std::vector<Tile> > tileGrid = 
            {{{NONE, NEITHER}, {GOOD, TWO}, {GOOD, TWO}, {GOOD, TWO}, {GOOD, TWO}, {NONE, NEITHER}},
            {{NONE, NEITHER}, {BAD, TWO}, {BAD, TWO}, {BAD, TWO}, {BAD, TWO}, {NONE, NEITHER}},
            {{NONE, NEITHER}, {NONE, NEITHER}, {NONE, NEITHER}, {NONE, NEITHER}, {NONE, NEITHER}, {NONE, NEITHER}},
            {{NONE, NEITHER}, {NONE, NEITHER}, {NONE, NEITHER}, {NONE, NEITHER}, {NONE, NEITHER}, {NONE, NEITHER}},
            {{NONE, NEITHER}, {BAD, ONE}, {BAD, ONE}, {BAD, ONE}, {BAD, ONE}, {NONE, NEITHER}},
            {{NONE, NEITHER}, {GOOD, ONE}, {GOOD, ONE}, {GOOD, ONE}, {GOOD, ONE}, {NONE, NEITHER}}};

        int enemyGoodCaptured = 0;
        int enemyBadCaptured = 0;

        bool host = true;
        bool turn;

        bool randomiseFirstMove();
        void takeMove(); // or return MOVE information
        void waitForMove(); // or return MOVE information

        bool selected = false;
        int selectedX = -1;
        int selectedY = -1;
        Tile selectedTile;

        bool suggested = false;
        int suggestedX = -1;
        int suggestedY = -1;
        Tile suggestedTile;

        void setTileAsSelected(int x, int y);
        void setTileAsSuggested(int x, int y);
        void deselectTile();
        void desuggestTile()
        bool surroundingSelectedTile(int x, int y);
        void processMoveInfo(Tile& tile)
        bool withinGrid(int x, int y);
        void mouseClickLeft(int xPos, int yPos);
        void checkForGameOver()

        //temporary
        std::string winString;
        std::string loseString;
};
