#include <framework/application/application.h>
#include <framework/input/inputhandler.h>
#include <framework/util/sfml/sfmlinputbackend.h>
#include <framework/input/actionhandler.h>
#include <framework/window/window.h>
#include <framework/util/sfml/sfmlwindowbackend.h>
#include <framework/application/gamestatemachine.h>
#include <SFML/Graphics.hpp>
#include "sfgui.h"
#include "renderer.h"
#include "networker.h"
#include "tile.h"
#include <iostream>

class GhostHunt : public windstorm::Application
{
    public:
        void setup() override;
        void destroy() override; 
        void loop() override;
    private:
        windstorm::GameStateMachine stateMachine;
        Networker networker;
        Renderer renderer;
        TileGrid grid;
        Clicky clicky;

        sf::RenderWindow sfWindow;
        windbreeze::SFMLWindowBackend sfmlWindowBackend = sfWindow;
        windbreeze::Window window = sfmlWindowBackend;

        windbreeze::SFMLInputBackend sfmlInputBackend = sfWindow;
        windbreeze::InputHandler inputHandler = sfmlInputBackend;
        windbreeze::ActionHandler<std::string> actionHandler;

};
