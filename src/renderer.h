#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "tile.h"

class Renderer
{
    public:
        Renderer();
        void render(sf::RenderWindow& window, std::vector<std::vector<Tile> >& grid);
        void renderText(sf::RenderWindow& window, std::string& string);
        int getTileSize();
        void setSelectedTile(int x, int y);
    private:
        int tileSize;
        
        bool selected;
        int selectedX;
        int selectedY;

        sf::Texture dungeonTexture;
        sf::Sprite dungeonSprite;
        sf::Sprite dungeonSelectedSprite;
        sf::Texture ghostTexture;
        sf::Sprite ghostSpriteUnknown;
        sf::Sprite ghostSpriteGood;
        sf::Sprite ghostSpriteBad;

        //move this later or something, unless i put the renderer in the main applicatoin as opposed to thes tates
        sf::Font font;
        sf::Text text;
};
