#include "renderer.h"

Renderer::Renderer(sf::RenderWindow& w, TileGrid& g) : window(w), grid(g)
{
    tileSize = 100;
    dungeonTexture.loadFromFile("data/dungeon.png");
    dungeonSprite.setTexture(dungeonTexture);
    dungeonSelectedSprite.setTexture(dungeonTexture);
    dungeonReadySprite.setTexture(dungeonTexture);
    dungeonMouseSprite.setTexture(dungeonTexture);
    dungeonSprite.setTextureRect(sf::IntRect(0, 0, 100, 100));
    dungeonSelectedSprite.setTextureRect(sf::IntRect(100, 0, 100, 100));
    dungeonReadySprite.setTextureRect(sf::IntRect(200, 0, 100, 100));
    dungeonMouseSprite.setTextureRect(sf::IntRect(300, 0, 100, 100));
    
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

void Renderer::render(bool host, int mouseX, int mouseY)
{
    window.clear();
    int selectedX = grid.getSelectedCoords().x;
    int selectedY = grid.getSelectedCoords().y;
    int suggestedX = grid.getSuggestedCoords().x;
    int suggestedY = grid.getSuggestedCoords().y;

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            const Tile& currentTile = grid.getTileAt(i, j);
            int x = i * tileSize;
            int y = j * tileSize;
            int mouseTileX = mouseX / tileSize;
            int mouseTileY = mouseY / tileSize;

            drawGameplayDungeons(i, j, x, y, mouseTileX, mouseTileY);
            drawGhosts(x, y);
        }
    }

    window.display();
}

void Renderer::renderSetup(bool host, int mouseX, int mouseY)
{
    window.clear();

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            const Tile& currentTile = grid.getTileAt(i, j);
            int x = i * tileSize;
            int y = j * tileSize;
            int mouseTileX = mouseX / tileSize;
            int mouseTileY = mouseY / tileSize;

            drawSetupDungeons(i, j, x, y, mouseTileX, mouseTileY);
            drawGhosts(x, y);
        }
    }
    drawPlaceGhostText();

    window.display();
}

void Renderer::renderText(std::string& string)
{
    window.clear();
    text.setString(string);

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            int x = j * 5 * tileSize;
            int y = i * tileSize;

            text.setPosition(x, y);
            window.draw(text);
        }
    }

    window.display();
}

void Renderer::drawGameplayDungeons()
{
    int selectedX = grid.getSelectedCoords().x;
    int selectedY = grid.getSelectedCoords().y;
    int suggestedX = grid.getSuggestedCoords().x;
    int suggestedY = grid.getSuggestedCoords().y;

    if (i == selectedX && j == selectedY)
    {
        dungeonSelectedSprite.setPosition(selectedX * tileSize, selectedY * tileSize);
        window.draw(dungeonSelectedSprite);
    }
    else if (i == mouseTileX && j == mouseTileY)
    {
        dungeonMouseSprite.setPosition(mouseTileX * tileSize, mouseTileY * tileSize);
        window.draw(dungeonMouseSprite);
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
}

void Renderer::drawSetupDungeons()
{
    int selectedX = grid.getSelectedCoords().x;
    int selectedY = grid.getSelectedCoords().y;
    int suggestedX = grid.getSuggestedCoords().x;
    int suggestedY = grid.getSuggestedCoords().y;

    if (i == selectedX && j == selectedY)
    {
        dungeonSelectedSprite.setPosition(selectedX * tileSize, selectedY * tileSize);
        window.draw(dungeonSelectedSprite);
    }
    else if (i == mouseTileX && j == mouseTileY)
    {
        dungeonMouseSprite.setPosition(mouseTileX * tileSize, mouseTileY * tileSize);
        window.draw(dungeonMouseSprite);
    }
    else if ((currentTile.playerState == ONE) && ((i > 0 && i < 5) && (j > 3 && j < 6)))
    {
        dungeonReadySprite.setPosition(x, y);
        window.draw(dungeonReadySprite);
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
}

void drawGhosts(int x, int y)
{
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

void Renderer::drawPlaceGhostText()
{
    std::string string = "Position your ghosts!";
    text.setString(string);
    text.setPosition(1 * tileSize, 3 * tileSize);
    window.draw(text);
}
