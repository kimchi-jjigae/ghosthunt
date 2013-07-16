#include <framework/structure.h>
#include <framework/userinterface.h>
#include <framework/util/input/sfmlinputbackend.h>
#include <framework/util/input/sfmlwindowbackend.h>
#include <SFML/Graphics.hpp>
//#include "sfgui.h"
#include "renderer.h"
#include "networker.h"
#include <iostream>

class MenuState : public windstorm::GameState
{
    public:
        //virtual void activate(std::string previousState) {}
        //virtual void deactivate(std::string nextState) {}
        //virtual void handOver(std::weak_ptr<GameState> previousState, std::string previousStateName) {}
        MenuState(sf::RenderWindow& sfw, windbreeze::InputHandler& ih, windbreeze::ActionHandler<std::string>& ah, Networker& nw, Renderer& r) : sfWindow(sfw), inputHandler(ih), actionHandler(ah), networker(nw), renderer(r) {}
        //MenuState(sf::RenderWindow& sfw, windbreeze::InputHandler& ih, windbreeze::ActionHandler<std::string>& ah, Networker& nw, Renderer& r, Clicky& c) : sfWindow(sfw), inputHandler(ih), actionHandler(ah), networker(nw), renderer(r), clicky(c) {}
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
        //Clicky& clicky;
        //sf::Clock clock;

        std::string nextState;
        bool connected;

        //sf::Event haxEventConversion(windbreeze::Event event);
};
