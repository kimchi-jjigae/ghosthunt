#include "renderer.h"

Renderer::Renderer()
{
    tileSize = 100;
    dungeonTexture.loadFromFile("data/dungeon.png");
    dungeonSprite.setTexture(dungeonTexture);
    dungeonSelectedSprite.setTexture(dungeonTexture);
    dungeonSprite.setTextureRect(sf::IntRect(0, 0, 100, 100));
    dungeonSelectedSprite.setTextureRect(sf::IntRect(100, 0, 100, 100));
    
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

int Renderer::getTileSize()
{
    return tileSize;
}

void Renderer::render(sf::RenderWindow& window, const TileGrid& grid, bool host)
{
    window.clear();
    
    int selectedX = grid.getSelectedCoords().x;
    int selectedY = grid.getSelectedCoords().y;
    int suggestedX = grid.getSuggestedCoords().x;
    int suggestedY = grid.getSuggestedCoords().y;

    //iterate through the grid
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            const Tile& currentTile = grid.getTileAt(i, j);
            int x = i * tileSize;
            int y = j * tileSize;

            //draw dungeon grid
            if (i == selectedX && j == selectedY)
            {
                dungeonSelectedSprite.setPosition(selectedX * tileSize, selectedY * tileSize);
                window.draw(dungeonSelectedSprite);
            }
            else if (i == suggestedX && j == suggestedY)
            {
                dungeonSelectedSprite.setPosition(suggestedX * tileSize, suggestedY * tileSize);
                window.draw(dungeonSelectedSprite);
            }
            else
            {
                dungeonSprite.setPosition(x, y);
                window.draw(dungeonSprite);
            }

            //draw ghosts
            /*
            if (currentTile.playerState == TWO)
            {
                */
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
                /*
            }
            else if (currentTile.playerState == ONE)
            {
                ghostSpriteUnknown.setPosition(x, y);
                window.draw(ghostSpriteUnknown);
            }
            */
        }
    }

    window.display();
}

void Renderer::renderText(sf::RenderWindow& window, std::string& string)
{
    window.clear();
    text.setString(string);

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            int x = j * 5 * tileSize;
            int y = i * tileSize;

            text.setPosition(x,y);
            window.draw(text);
        }
    }

    window.display();
}
