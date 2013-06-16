#pragma once
#include <iostream>
enum GhostState { NONE, GOOD, BAD };
enum PlayerState { NEITHER, ONE, TWO };

struct Tile
{
    GhostState ghostState;
    PlayerState playerState;
};

class TileGrid
{
    public:
        void setTileAsSelected(int x, int y);
        void setTileAsSuggested(int x, int y);
        void deselectTile();
        void desuggestTile();

        bool withinGrid(int x, int y);
        bool surroundingSelectedTile(int x, int y);
        bool isSuggested();

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
        int selectedX = -1;
        int selectedY = -1;

        bool suggested = false;
        int suggestedX = -1;
        int suggestedY = -1;
};
