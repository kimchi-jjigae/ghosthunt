#include "renderer.h"

Renderer::Renderer()
{
    tileSize = 32;
    dungeonTexture.loadFromFile("../data/dungeon.png");
    dungeonSprite(dungeonTexture);
}

void Renderer::render()
{
    window.clear();
    
    //draw dungeon grid
    for (i = 0, i < 6, i++)
    {
        for (j = 0, j < 6, j++)
        {
            dungeonSprite.setPosition(i * tileSize, j * tileSize);
            window.draw(dungeonSprite);
        }
    }

    window.display();
}
