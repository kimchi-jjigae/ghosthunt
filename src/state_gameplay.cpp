#include "state_gameplay.h"

GameplayState::GameplayState(sf::RenderWindow& sfw, windbreeze::InputHandler& ih, windbreeze::ActionHandler<std::string>& ah)
{
    std::cout << "LOL\n";
}

void GameplayState::setup()
{
    std::string BAJS = "BAJS";
}

std::string GameplayState::run()
{
    std::cout << BAJS << "\n";
}
