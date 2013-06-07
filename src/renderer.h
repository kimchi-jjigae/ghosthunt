#include <iostream>
#include <SFML/Graphics.hpp>

class Renderer
{
    public:
        Renderer();
    private:
        int tileSize;
        sf::Texture dungeonTexture;
        sf::Sprite dungeonSprite;
};
