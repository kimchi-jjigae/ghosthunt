#include <framework/structure.h>
#include <framework/userinterface.h>
#include <framework/util/input/sfmlinputbackend.h>
#include <framework/util/input/sfmlwindowbackend.h>
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

    private:
        sf::RenderWindow& sfWindow;
        windbreeze::InputHandler& inputHandler;
        windbreeze::ActionHandler<std::string>& actionHandler;
        Networker& networker;
        Renderer& renderer;
        TileGrid& grid;

        std::thread listenThread;

        bool host;
        bool waiting = false;
        bool received = false;
        bool sentSetup = false;
        void listenForSignal();
        void eventLoop();
        void placeEnemyGhosts();
        sf::Packet listenPacket; 
        sf::Packet setupPacket;
        std::string enemyGhosts;
        std::string nextState;
        void mouseClickLeft(int xPos, int yPos);
};
