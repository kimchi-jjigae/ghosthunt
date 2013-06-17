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
#include <iostream>
#include <thread>
#include <unistd.h> // for sleep

class SetupState : public windstorm::GameState
{
    public:
        void activate(std::string previousState) override;
        //virtual void deactivate(std::string nextState) {}
        //virtual void handOver(std::weak_ptr<GameState> previousState, std::string previousStateName) {}
        SetupState(sf::RenderWindow& sfw, windbreeze::InputHandler& ih, windbreeze::ActionHandler<std::string>& ah, Networker& nw, Renderer& r, TileGrid& tg) : sfWindow(sfw), inputHandler(ih), actionHandler(ah), networker(nw), renderer(r), grid(tg){}
        //void setup() override;
        std::string run() override;
        //virtual void destroy() {}
        //virtual ~GameState() {}

        bool isTurn();

    private:
        sf::RenderWindow& sfWindow;
        windbreeze::InputHandler& inputHandler;
        windbreeze::ActionHandler<std::string>& actionHandler;
        Networker& networker;
        Renderer& renderer;
        TileGrid& grid;

        bool randomiseFirstMove();
        void listenForSignal();
        void setupGhosts();
        void placeEnemyGhosts();
        std::string enemyState;

        std::string nextState;
        bool turn;
};
