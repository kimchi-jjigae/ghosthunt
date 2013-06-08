#include "state_gameplay.h"

void GameplayState::setup()
{
}

std::string GameplayState::run()
{
    renderer.render(sfWindow, tileGrid);
    return "";
}
