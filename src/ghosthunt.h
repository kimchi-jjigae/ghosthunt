#include <featherkit/structure.h>
#include <featherkit/userinterface.h>
#include <featherkit/render2d.h>
#include <featherkit/render2dutil.h>
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
        fea::GameStateMachine stateMachine;
        Renderer renderer = Renderer(sfWindow, grid);
        Networker networker;
        TileGrid grid;
        Clicky clicky;

        sf::RenderWindow sfWindow;
        fea::SFMLWindowBackend sfmlWindowBackend = sfWindow;
        wfea::Window window = sfmlWindowBackend;

        fea::SFMLInputBackend sfmlInputBackend = sfWindow;
        fea::InputHandler inputHandler = sfmlInputBackend;
        fea::ActionHandler<std::string> actionHandler;
};
