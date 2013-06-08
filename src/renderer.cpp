#include "renderer.h"

Renderer::Renderer()
{
    tileSize = 100;
    dungeonTexture.loadFromFile("data/dungeon.png");
    dungeonSprite.setTexture(dungeonTexture);
    
    ghostTexture.loadFromFile("data/ghost.png");
    ghostSpriteUnknown.setTexture(ghostTexture);
    ghostSpriteGood.setTexture(ghostTexture);
    ghostSpriteBad.setTexture(ghostTexture);
    ghostSpriteUnknown.setTextureRect(sf::IntRect(0, 0, 100, 100));
    ghostSpriteGood.setTextureRect(sf::IntRect(0, 100, 200, 100));
    ghostSpriteBad.setTextureRect(sf::IntRect(0, 200, 300, 100));
}

void Renderer::render(sf::RenderWindow& window, std::vector<std::vector<Tile> > tileArray);
{
    window.clear();
    
    //draw dungeon grid
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            dungeonSprite.setPosition(i * tileSize, j * tileSize);
            window.draw(dungeonSprite);
            if (tileArray[i][j].playerState == ONE)
            {
                if (tileArray.ghostState == GOOD)
                {
                    ghostSpriteGood.setPosition(i * tileSize, j * tileSize);
                    window.draw(ghostSpriteGood);
                }
                else if (tileArray.ghostState == BAD)
                {
                    ghostSpriteBad.setPosition(i * tileSize, j * tileSize);
                    window.draw(ghostSpriteBad);
                }
            }
            else if (tileArray.playerState == TWO)
            {
                ghostSpriteUnknown.setPosition(i * tileSize, j * tileSize);
                window.draw(ghostSpriteUnknown);
            }
        }
    }

    window.display();
}
