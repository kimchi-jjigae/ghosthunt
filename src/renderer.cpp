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
    font.loadFromFile("data/acmesa.TTF");
    text.setFont(font);
    text.setColor(sf::Color(255,0,0));
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
            int x = j * tileSize;
            int y = i * tileSize;

            //draw dungeon grid
            dungeonSprite.setPosition(x, y);
            window.draw(dungeonSprite);

            //draw ghosts
            if (currentTile.playerState == ONE)
            {
                if (currentTile.ghostState == GOOD)
                {
                    ghostSpriteGood.setPosition(x, y);
                    window.draw(ghostSpriteGood);
                }
                else if (currentTile.ghostState == BAD)
                {
                    ghostSpriteBad.setPosition(x, y);
                    window.draw(ghostSpriteBad);
                }
            }
            else if (currentTile.playerState == TWO)
            {
                ghostSpriteUnknown.setPosition(x, y);
                window.draw(ghostSpriteUnknown);
            }
        }
    }

    window.display();
}

void Renderer::renderText(sf::RenderWindow& window, std::string& string)
{
    text.setString(string);

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            int x = j * tileSize;
            int y = i * tileSize;

            window.draw(text);
        }
    }

    window.display();
}
