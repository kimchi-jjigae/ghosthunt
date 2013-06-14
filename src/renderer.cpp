#include "renderer.h"

Renderer::Renderer()
{
    selectedX = -1;
    selectedY = -1;
    suggestedX = -1;
    suggestedY = -1;
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

void Renderer::setSelectedTile(int x, int y)
{
    selectedX = x;
    selectedY = y;
}

void Renderer::setSuggestedTile(int x, int y)
{
    suggestedX = x;
    suggestedY = y;
}

void Renderer::render(sf::RenderWindow& window, const std::vector<std::vector<Tile> >& grid)
{
    window.clear();
    
    //iterate through the grid
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            Tile currentTile = grid.at(j).at(i);
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
