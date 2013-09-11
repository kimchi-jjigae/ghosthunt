// merge render functions
#pragma once
#include <iostream>
//#include <SFML/Graphics.hpp>
#include "tile.h"
#include <featherkit/render2d.h>
#include <featherkit/render2dutil.h>


class Renderer
{
    /*
    public:
        Renderer(sf::RenderWindow& w, TileGrid& g);
        void render(bool host, bool turn, int mouseX, int mouseY);
        void renderSetup(bool host, int mouseX, int mouseY);
        void renderText(std::string& string);
        void drawLastMove();
        int getTileSize();
        int getBorderSizeX();
        int getBorderSizeY();
        */

    public:

    private:
        void drawTextAtTop(std::string s);
        void drawGameplayDungeons(int i, int j, int mouseTileX, int mouseTileY);
        void drawSetupDungeons(int i, int j, int mouseTileX, int mouseTileY);
        void drawGhosts(int i, int j);

        int borderSizeX = 150;
        int borderSizeY = 50;
        int tileSize = 100;
        int iter = 0;
        sf::RenderWindow& window;
        TileGrid& grid;
        Tile currentTile;

        sf::Font font;
        sf::Text text;
        sf::Text text2;

    private:
        windbreeze::TextureManager<windbreeze::OpenGLTexture> textureManager;
        windbreeze::OpenGL2DBackend glBackend{textureManager};
        Renderer2D{glBackend, windbreeze::Viewport(800, 800)};

        windbreeze::SubRectQuad dungeonTile{100, 100};
        windbreeze::SubRectQuad dungeonSelectedTile{100, 100};
        windbreeze::SubRectQuad dungeonReadyTile{100, 100};
        windbreeze::SubRectQuad dungeonMouseTile{100, 100};
        windbreeze::SubRectQuad ghostSpriteUnknown{100, 100};
        windbreeze::SubRectQuad ghostSpriteGood{100, 100};
        windbreeze::SubRectQuad ghostSpriteBad{100, 100};


};
