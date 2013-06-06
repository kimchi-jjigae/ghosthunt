#include "ghosthunt.h"
#include "particlestate.h"
#include "splashstate.h"

void Particles::setup()
{
    window.create(windbreeze::VideoMode(1366, 768), "Particles");
    window.setFramerateLimit(60);

    stateMachine.addGameState("splash", std::shared_ptr<SplashState>(new SplashState(sfWindow, inputHandler)));
    stateMachine.addGameState("particles", std::shared_ptr<ParticleState>(new ParticleState(sfWindow, inputHandler, actionHandler)));
    stateMachine.setCurrentState("splash");
}

void Particles::destroy()
{
    window.close();
}

void Particles::loop()
{
    stateMachine.run();

    if(stateMachine.isFinished())
        quit();
}
