#pragma once
#include <iostream>
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
        Tile getTileAt(int x, int y);
        void setSelectedTile(int x, int y);
        void setSuggestedTile(int x, int y);
        Tile getSelectedTile()
        Tile getSuggestedTile()
        TileCoords getSelectedCoords();
        TileCoords getSuggestedCoords();
        void deselectTile();
        void desuggestTile();
        bool isSelected();
        bool isSuggested();

        bool withinGrid(int x, int y);
        bool surroundingSelectedTile(int x, int y);

    private:
        void modifyTileGhost(int x, int y, GhostState ghost);
        void modifyTilePlayer(int x, int y, PlayerState player);

        std::vector<std::vector<Tile> > grid = 
            {{{NONE, NEITHER}, {GOOD, TWO}, {GOOD, TWO}, {GOOD, TWO}, {GOOD, TWO}, {NONE, NEITHER}},
            {{NONE, NEITHER}, {BAD, TWO}, {BAD, TWO}, {BAD, TWO}, {BAD, TWO}, {NONE, NEITHER}},
            {{NONE, NEITHER}, {NONE, NEITHER}, {NONE, NEITHER}, {NONE, NEITHER}, {NONE, NEITHER}, {NONE, NEITHER}},
            {{NONE, NEITHER}, {NONE, NEITHER}, {NONE, NEITHER}, {NONE, NEITHER}, {NONE, NEITHER}, {NONE, NEITHER}},
            {{NONE, NEITHER}, {BAD, ONE}, {BAD, ONE}, {BAD, ONE}, {BAD, ONE}, {NONE, NEITHER}},
            {{NONE, NEITHER}, {GOOD, ONE}, {GOOD, ONE}, {GOOD, ONE}, {GOOD, ONE}, {NONE, NEITHER}}};

        bool selected = false;
        TileCoords selectCoords = {-1, -1};
        bool suggested = false;
        TileCoords suggestCoords = {-1, -1};
};
