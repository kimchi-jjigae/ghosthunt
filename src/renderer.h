// create draw ghosts, dungeon, etc. functions - private
// merge render functions
#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "tile.h"

class Renderer
{
    public:
        Renderer(sf::RenderWindow& w, TileGrid& g);
        void render(bool host, int mouseX, int mouseY);
        void renderSetup(bool host, int mouseX, int mouseY);
        void renderText(std::string& string);
        int getTileSize();

    private:
        void drawPlaceGhostText();
        void drawGameplayDungeons();
        void drawSetupDungeons();
        void drawGhosts();

        int tileSize;
        sf::RenderWindow& window;
        TileGrid& grid;
        
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
