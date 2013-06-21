// merge render functions
#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "tile.h"

class Renderer
{
    public:
        Renderer(sf::RenderWindow& w, TileGrid& g);
        void render(bool host, bool turn, int mouseX, int mouseY);
        void renderSetup(bool host, int mouseX, int mouseY);
        void renderText(std::string& string);
        int getTileSize();

    private:
        void drawTextInCentre(std::string s);
        void drawGameplayDungeons(int i, int j, int mouseTileX, int mouseTileY);
        void drawSetupDungeons(int i, int j, int mouseTileX, int mouseTileY);
        void drawGhosts(int i, int j);

        int tileSize;
        int iter = 0;
        sf::RenderWindow& window;
        TileGrid& grid;
        Tile currentTile;
        
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
