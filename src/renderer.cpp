#include "renderer.h"

Renderer::Renderer()
{
    tileSize = 100;
    dungeonTexture.loadFromFile("data/dungeon.png");
    dungeonSprite.setTexture(dungeonTexture);
}

void Renderer::render(sf::RenderWindow& window)
{
    window.clear();
    
    //draw dungeon grid
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            dungeonSprite.setPosition(i * tileSize, j * tileSize);
            window.draw(dungeonSprite);
        }
    }

    window.display();
}
