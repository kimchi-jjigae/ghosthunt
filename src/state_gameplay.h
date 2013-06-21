#include <framework/application/gamestate.h>
#include <framework/input/inputhandler.h>
#include <framework/util/sfml/sfmlinputbackend.h>
#include <framework/input/actionhandler.h>
#include <framework/window/window.h>
#include <framework/util/sfml/sfmlwindowbackend.h>
#include <framework/application/gamestatemachine.h>
#include <SFML/Graphics.hpp>
#include "renderer.h"
#include "networker.h"
#include "tile.h"
#include <thread>
#include <iostream>
#include <stdlib.h> // for rand

class GameplayState : public windstorm::GameState
{
    public:
        void activate(std::string previousState) override;
        //virtual void deactivate(std::string nextState) {}
        GameplayState(sf::RenderWindow& sfw, windbreeze::InputHandler& ih, windbreeze::ActionHandler<std::string>& ah, Networker& nw, Renderer& r, TileGrid& tg) : sfWindow(sfw), inputHandler(ih), actionHandler(ah), networker(nw), renderer(r), grid(tg){}
        std::string run() override;
        //virtual void destroy() {}
        //virtual ~GameState() {}

    private:
        sf::RenderWindow& sfWindow;
        windbreeze::InputHandler& inputHandler;
        windbreeze::ActionHandler<std::string>& actionHandler;
        Networker& networker;
        Renderer& renderer;
        TileGrid& grid;
        std::string nextState;

        int enemyGoodCaptured = 0;
        int enemyBadCaptured = 0;
        bool turn;
        bool host;
        bool waiting = false;
        int gameOver = 0;

        std::thread waitThread;

        void waitForTurn();
        void eventLoop();
        void processMoveInfo();
        void mouseClickLeft(int xPos, int yPos);
        sf::Packet convertMoveToString();
        bool randomiseFirstMove();
        void checkForGameOver();
        void bregott();

        sf::Packet packet;

        //temporary
        std::string winString;
        std::string loseString;

        int mouseX;
        int mouseY;
};
