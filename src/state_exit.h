#include <framework/application/gamestate.h>
#include <framework/input/inputhandler.h>
#include <framework/util/sfml/sfmlinputbackend.h>
#include <framework/window/window.h>
#include <framework/util/sfml/sfmlwindowbackend.h>
#include <framework/application/gamestatemachine.h>
#include <SFML/Graphics.hpp>
#include "renderer.h"
#include <iostream>

class ExitState : public windstorm::GameState
{
    public:
        ExitState(sf::RenderWindow& sfw, windbreeze::InputHandler& ih, Renderer& r) : sfWindow(sfw), inputHandler(ih), renderer(r) {}
        void setup() override;
        std::string run() override;
    private:
        sf::RenderWindow& sfWindow;
        windbreeze::InputHandler& inputHandler;
        Renderer renderer;

        std::string textString;
};
