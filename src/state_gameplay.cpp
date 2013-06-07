#include "state_gameplay.h"

void GameplayState::setup()
{
    BAJS = "bajs";
}

std::string GameplayState::run()
{
    std::cout << BAJS << "\n";
    return "";
}
