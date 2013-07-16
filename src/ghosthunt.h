#include <framework/structure.h>
#include <framework/userinterface.h>
#include <framework/util/input/sfmlinputbackend.h>
#include <framework/util/input/sfmlwindowbackend.h>
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
        Renderer renderer = Renderer(sfWindow, grid);
        Networker networker;
        TileGrid grid;
        Clicky clicky;

        sf::RenderWindow sfWindow;
        windbreeze::SFMLWindowBackend sfmlWindowBackend = sfWindow;
        windbreeze::Window window = sfmlWindowBackend;

        windbreeze::SFMLInputBackend sfmlInputBackend = sfWindow;
        windbreeze::InputHandler inputHandler = sfmlInputBackend;
        windbreeze::ActionHandler<std::string> actionHandler;
};
