#include "renderer.h"

Renderer::Renderer()
{
        tileSize = 32;
        dungeonTexture.loadFromFile("../data/dungeon.png");
        dungeonSprite(dungeonTexture);

}
