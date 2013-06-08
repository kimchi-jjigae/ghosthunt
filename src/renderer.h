#include <iostream>
#include <SFML/Graphics.hpp>
#include "tile.h"

class Renderer
{
    public:
        Renderer();
        void render(sf::RenderWindow& window, std::vector<std::vector<Tile> > tileArray);
    private:
        int tileSize;
        sf::Texture dungeonTexture;
        sf::Sprite dungeonSprite;
        sf::Texture ghostTexture;
        sf::Sprite ghostSpriteUnknown;
        sf::Sprite ghostSpriteGood;
        sf::Sprite ghostSpriteBad;
};
