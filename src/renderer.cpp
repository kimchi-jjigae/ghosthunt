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
    font.loadFromFile("data/acmesab.TTF");
    text.setFont(font);
    text.setColor(sf::Color(100,100,255));
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
            currentTile = grid.getTileAt(i, j);
            int x = i * tileSize;
            int y = j * tileSize;
            int mouseTileX = (mouseX - window.getPosition().x) / tileSize;  // need to truncate, not round these up
            int mouseTileY = (mouseY - window.getPosition().y) / tileSize;

            drawGameplayDungeons(i, j, mouseTileX, mouseTileY);
            drawGhosts(i, j);
        }
    }
    if (iter < 360 + 180)
    {
        drawTextInCentre("The game begins now!");
        iter++;
    }
    else if (iter < 360 + 360)
    {
        drawTextInCentre("Your move.");
        iter++;
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
            currentTile = grid.getTileAt(i, j);
            int mouseTileX = (mouseX - window.getPosition().x) / tileSize;  // need to truncate, not round these up
            int mouseTileY = (mouseY - window.getPosition().y) / tileSize;

            drawSetupDungeons(i, j, mouseTileX, mouseTileY);
            drawGhosts(i, j);
        }
    }
    if (iter < 180)
    {
        drawTextInCentre("Position your ghosts...");
        iter++;
    }
    else if (iter < 360)
    {
        drawTextInCentre("...press K when you are ready!");
        iter++;
    }

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

void Renderer::drawGameplayDungeons(int i, int j, int mouseTileX, int mouseTileY)
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
    else if (i == suggestedX && j == suggestedY)
    {
        dungeonSelectedSprite.setPosition(suggestedX * tileSize, suggestedY * tileSize);
        window.draw(dungeonSelectedSprite);
    }
    else if (i == mouseTileX && j == mouseTileY)
    {
        dungeonMouseSprite.setPosition(mouseTileX * tileSize, mouseTileY * tileSize);
        window.draw(dungeonMouseSprite);
    }
    else
    {
        dungeonSprite.setPosition(i * tileSize, j * tileSize);
        window.draw(dungeonSprite);
    }
}

void Renderer::drawSetupDungeons(int i, int j, int mouseTileX, int mouseTileY)
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
        dungeonReadySprite.setPosition(i * tileSize, j * tileSize);
        window.draw(dungeonReadySprite);
    }
    else if (i == suggestedX && j == suggestedY)
    {
        dungeonSelectedSprite.setPosition(suggestedX * tileSize, suggestedY * tileSize);
        window.draw(dungeonSelectedSprite);
    }
    else
    {
        dungeonSprite.setPosition(i * tileSize, j * tileSize);
        window.draw(dungeonSprite);
    }
}

void Renderer::drawGhosts(int i, int j)
{
    int x = i * tileSize;
    int y = j * tileSize;
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

void Renderer::drawTextInCentre(std::string s)
{
    text.setString(s);
    text.setCharacterSize(25);
    int centre = (text.getGlobalBounds().width)/2;
    int height = (text.getGlobalBounds().height);
    text.setPosition(3 * tileSize - centre, 3 * tileSize - 50);
    window.draw(text);
}
