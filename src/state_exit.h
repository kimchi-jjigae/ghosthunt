#include <framework/structure.h>
#include <framework/userinterface.h>
#include <framework/util/input/sfmlinputbackend.h>
#include <framework/util/input/sfmlwindowbackend.h>
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
