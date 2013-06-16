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

class MenuState : public windstorm::GameState
{
    public:
        //virtual void activate(std::string previousState) {}
        //virtual void deactivate(std::string nextState) {}
        //virtual void handOver(std::weak_ptr<GameState> previousState, std::string previousStateName) {}
        MenuState(sf::RenderWindow& sfw, windbreeze::InputHandler& ih, windbreeze::ActionHandler<std::string>& ah, Networker& nw, Renderer& r) : sfWindow(sfw), inputHandler(ih), actionHandler(ah), networker(nw), renderer(r){}
        void setup() override;
        std::string run() override;
        //virtual void destroy() {}
        //virtual ~GameState() {}

    private:
        sf::RenderWindow& sfWindow;
        windbreeze::InputHandler& inputHandler;
        windbreeze::ActionHandler<std::string>& actionHandler;
        Networker& networker;
        Renderer& renderer;

        std::string nextState;
        bool connected;
};
