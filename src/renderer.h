// create draw ghosts, dungeon, etc. functions - private
// merge render functions
#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "tile.h"

class Renderer
{
    public:
        Renderer(sf::RenderWindow& window);
        void render(const TileGrid& grid, bool host, int mouseX, int mouseY);
        void renderSetup(const TileGrid& grid, bool host, int mouseX, int mouseY);
        void renderText(std::string& string);
        int getTileSize();

    private:
        void drawPlaceGhostText();
        void drawGameplayDungeons(int i, int j, int x, int y, int mouseTileX, int mouseTileY);
        void drawSetupDungeons(int i, int j, int x, int y, int mouseTileX, int mouseTileY);
        void drawGhosts(int x, int y);

        int tileSize;
        sf::RenderWindow& window;
        
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
