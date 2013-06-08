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
    ghostSpriteGood.setTextureRect(sf::IntRect(100, 0, 100, 100));
    ghostSpriteBad.setTextureRect(sf::IntRect(200, 0, 100, 100));
}

void Renderer::render(sf::RenderWindow& window, std::vector<std::vector<Tile> >& grid)
{
    window.clear();
    
    //iterate through the grid
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            Tile currentTile = grid[i][j];
            int x = i * tileSize;
            int y = j * tileSize;

            //draw dungeon grid
            dungeonSprite.setPosition(x, y);
            window.draw(dungeonSprite);

            //draw ghosts
            if (currentTile.playerState == ONE)
            {
                std::cout << "one bajs\n";
                if (currentTile.ghostState == GOOD)
                {
                std::cout << "good bajs\n";
                    ghostSpriteGood.setPosition(x, y);
                    window.draw(ghostSpriteGood);
                }
                else if (currentTile.ghostState == BAD)
                {
                std::cout << "bad bajs\n";
                    ghostSpriteBad.setPosition(x, y);
                    window.draw(ghostSpriteBad);
                }
            }
            else if (currentTile.playerState == TWO)
            {
                std::cout << "two bajs\n";
                ghostSpriteUnknown.setPosition(x, y);
                window.draw(ghostSpriteUnknown);
            }
        }
    }

    window.display();
}
