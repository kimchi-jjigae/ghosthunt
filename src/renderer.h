#include <iostream>
#include <SFML/Graphics.hpp>
#include "tile.h"

class Renderer
{
    public:
        Renderer();
        void render();
    private:
        int tileSize;
        sf::Texture dungeonTexture;
        sf::Sprite dungeonSprite;
};
