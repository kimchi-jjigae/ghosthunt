#include "renderer.h"

Renderer::Renderer(sf::RenderWindow& w, TileGrid& g) : window(w), grid(g)
{
    windbreeze::OpenGLTextureCreator creator;
    sf::Image dungeonTexture;
    dungeonTexture.loadFromFile("data/dungeon.png");

    textureManager.addTexture("dungeonTexture", creator.createTexture(dungeonTexture.getPixelsPtr(), 100, 100)); // texture ready to be used now! ^_^

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
    text.setFont(font);
    text.setColor(sf::Color(100,100,255));
}

int Renderer::getTileSize()
{
    return tileSize;
}

int Renderer::getBorderSizeX()
{
    return borderSizeX;
}

int Renderer::getBorderSizeY()
{
    return borderSizeY;
}

void Renderer::render(bool host, bool turn, int mouseX, int mouseY)
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
            int mouseTileX = (mouseX - window.getPosition().x - borderSizeX) / tileSize;  // need to truncate, not round these up
            int mouseTileY = (mouseY - window.getPosition().y - borderSizeY) / tileSize;

            drawGameplayDungeons(i, j, mouseTileX, mouseTileY);
            drawGhosts(i, j);
        }
    }
    if (iter < 360 + 180)       // make this independent of the other render function :O maybe when you mix them
    {
        drawTextAtTop("The game begins now!");
        iter++;
    }
    else if (turn)
    {
        drawTextAtTop("Your move.");
    }
    else if (!turn)
    {
        drawTextAtTop("Waiting for the other player.");
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
            int mouseTileX = (mouseX - window.getPosition().x - borderSizeX) / tileSize;  // need to truncate, not round these up
            int mouseTileY = (mouseY - window.getPosition().y - borderSizeY) / tileSize;

            drawSetupDungeons(i, j, mouseTileX, mouseTileY);
            drawGhosts(i, j);
        }
    }
    if (iter < 180)
    {
        drawTextAtTop("Position your ghosts...");
        iter++;
    }
    else if (iter < 360)
    {
        drawTextAtTop("...press K when you are ready!");
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

            text.setPosition(x + borderSizeX, y + borderSizeY);
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
        dungeonSelectedSprite.setPosition(selectedX * tileSize + borderSizeX, selectedY * tileSize + borderSizeY);
        window.draw(dungeonSelectedSprite);
    }
    else if (i == suggestedX && j == suggestedY)
    {
        dungeonSelectedSprite.setPosition(suggestedX * tileSize + borderSizeX, suggestedY * tileSize + borderSizeY);
        window.draw(dungeonSelectedSprite);
    }
    else if (i == mouseTileX && j == mouseTileY)
    {
        dungeonMouseSprite.setPosition(mouseTileX * tileSize + borderSizeX, mouseTileY * tileSize + borderSizeY);
        window.draw(dungeonMouseSprite);
    }
    else
    {
        dungeonSprite.setPosition(i * tileSize + borderSizeX, j * tileSize + borderSizeY);
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
        dungeonSelectedSprite.setPosition(selectedX * tileSize + borderSizeX, selectedY * tileSize + borderSizeY);
        window.draw(dungeonSelectedSprite);
    }
    else if (i == mouseTileX && j == mouseTileY)
    {
        dungeonMouseSprite.setPosition(mouseTileX * tileSize + borderSizeX, mouseTileY * tileSize + borderSizeY);
        window.draw(dungeonMouseSprite);
    }
    else if ((currentTile.playerState == ONE) && ((i > 0 && i < 5) && (j > 3 && j < 6)))
    {
        dungeonReadySprite.setPosition(i * tileSize + borderSizeX, j * tileSize + borderSizeY);
        window.draw(dungeonReadySprite);
    }
    else if (i == suggestedX && j == suggestedY)
    {
        dungeonSelectedSprite.setPosition(suggestedX * tileSize + borderSizeX, suggestedY * tileSize + borderSizeY);
        window.draw(dungeonSelectedSprite);
    }
    else
    {
        dungeonSprite.setPosition(i * tileSize + borderSizeX, j * tileSize + borderSizeY);
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
            ghostSpriteGood.setPosition(x + borderSizeX, y + borderSizeY);
            window.draw(ghostSpriteGood);
        }
        else if (currentTile.ghostState == BAD)
        {
            ghostSpriteBad.setPosition(x + borderSizeX, y + borderSizeY);
            window.draw(ghostSpriteBad);
        }
    }
    else if (currentTile.playerState == TWO)
    {
        ghostSpriteUnknown.setPosition(x + borderSizeX, y + borderSizeY);
        window.draw(ghostSpriteUnknown);
    }
}

void Renderer::drawTextAtTop(std::string s)
{
    text.setString(s);
    text.setCharacterSize(25);
    int centre = (text.getGlobalBounds().width)/2;
    int height = (text.getGlobalBounds().height);
    text.setPosition(3 * tileSize - centre + borderSizeX, (borderSizeY - height)/2);
    window.draw(text);
}

void Renderer::drawLastMove()
{
    std::string s;
    s = "bajs";
    text2.setString(s);
    text2.setCharacterSize(25);
    int centre = (text.getGlobalBounds().width)/2;
    int height = (text.getGlobalBounds().height);
    //text.setPosition(3 * tileSize - centre + borderSizeX, 6 * tileSize + (borderSizeY - height)/2);
    text.setPosition(3 * tileSize - centre + borderSizeX, (borderSizeY - height)/2);
    window.draw(text);
    std::cout << "hej\n";
}
