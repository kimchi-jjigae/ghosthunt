#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "tile.h"

class Renderer
{
    public:
        Renderer();
        void render(sf::RenderWindow& window, const std::vector<std::vector<Tile> >& grid);
        void renderText(sf::RenderWindow& window, std::string& string);
        int getTileSize();
        void setSelectedTile(int x, int y);
        void setSuggestedTile(int x, int y);
    private:
        int tileSize;
        
        int selectedX;
        int selectedY;
        int suggestedX;
        int suggestedY;

        sf::Texture dungeonTexture;
        sf::Sprite dungeonSprite;
        sf::Sprite dungeonSelectedSprite;
        sf::Texture ghostTexture;
        sf::Sprite ghostSpriteUnknown;
        sf::Sprite ghostSpriteGood;
        sf::Sprite ghostSpriteBad;

        sf::Font font;
        sf::Text text;
};
