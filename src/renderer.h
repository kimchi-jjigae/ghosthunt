#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "tile.h"

class Renderer
{
    public:
        Renderer();
        void render(sf::RenderWindow& window, const TileGrid& grid, bool host);
        void renderSetup(sf::RenderWindow& window, const TileGrid& grid, bool host, int mouseX, int mouseY);
        void renderText(sf::RenderWindow& window, std::string& string);
        int getTileSize();

    private:
        int tileSize;
        
        sf::Texture dungeonTexture;
        sf::Sprite dungeonSprite;
        sf::Sprite dungeonSelectedSprite;
        sf::Sprite dungeonReadySprite;
        sf::Sprite dungeonMouseSprite;
        sf::Texture ghostTexture;
        sf::Sprite ghostSpriteUnknown;
        sf::Sprite ghostSpriteGood;
        sf::Sprite ghostSpriteBad;

        sf::Font font;
        sf::Text text;
};
