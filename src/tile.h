#pragma once
#include <vector>
#include <iostream>
#include <SFML/Network.hpp>

enum GhostState { NONE, GOOD, BAD };
enum PlayerState { NEITHER, ONE, TWO };

struct Tile
{
    GhostState ghostState;
    PlayerState playerState;
};

struct TileCoords
{
    int x;
    int y;
};

class TileGrid
{
    public:
        Tile getTileAt(int x, int y) const;
        void moveSelectToSuggest();
        void swapSelectAndSuggest();

        void setSelectedTile(int x, int y);
        void setSuggestedTile(int x, int y);
        Tile getSelectedTile() const;
        Tile getSuggestedTile() const;
        TileCoords getSelectedCoords() const;
        TileCoords getSuggestedCoords() const;
        void deselectTile();
        void desuggestTile();
        bool isSelected();
        bool isSuggested();

        bool withinGrid(int x, int y);
        bool surroundingSelectedTile(int x, int y);
        void placeEnemyGhosts(std::string enemyState);
        bool checkIfSetupValid();
        sf::Packet convertPositionsToPacket();
        sf::Packet convertMoveToPacket();

    private:
        std::vector<std::vector<Tile> > grid = 
            {{{NONE, NEITHER}, {GOOD, TWO}, {GOOD, TWO}, {GOOD, TWO}, {GOOD, TWO}, {NONE, NEITHER}},
            {{NONE, NEITHER}, {BAD, TWO}, {BAD, TWO}, {BAD, TWO}, {BAD, TWO}, {NONE, NEITHER}},
            {{NONE, NEITHER}, {NONE, NEITHER}, {NONE, NEITHER}, {NONE, NEITHER}, {NONE, NEITHER}, {NONE, NEITHER}},
            {{NONE, NEITHER}, {NONE, NEITHER}, {NONE, NEITHER}, {NONE, NEITHER}, {NONE, NEITHER}, {NONE, NEITHER}},
            {{NONE, NEITHER}, {BAD, ONE}, {BAD, ONE}, {BAD, ONE}, {BAD, ONE}, {NONE, NEITHER}},
            {{NONE, NEITHER}, {GOOD, ONE}, {GOOD, ONE}, {GOOD, ONE}, {GOOD, ONE}, {NONE, NEITHER}}};

        bool selected = false;
        TileCoords selectedCoords = {-1, -1};
        bool suggested = false;
        TileCoords suggestedCoords = {-1, -1};
};
