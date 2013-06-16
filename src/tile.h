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

    private:
        std::vector<std::vector<Tile> > tileGrid = 
            {{{NONE, NEITHER}, {GOOD, TWO}, {GOOD, TWO}, {GOOD, TWO}, {GOOD, TWO}, {NONE, NEITHER}},
            {{NONE, NEITHER}, {BAD, TWO}, {BAD, TWO}, {BAD, TWO}, {BAD, TWO}, {NONE, NEITHER}},
            {{NONE, NEITHER}, {NONE, NEITHER}, {NONE, NEITHER}, {NONE, NEITHER}, {NONE, NEITHER}, {NONE, NEITHER}},
            {{NONE, NEITHER}, {NONE, NEITHER}, {NONE, NEITHER}, {NONE, NEITHER}, {NONE, NEITHER}, {NONE, NEITHER}},
            {{NONE, NEITHER}, {BAD, ONE}, {BAD, ONE}, {BAD, ONE}, {BAD, ONE}, {NONE, NEITHER}},
            {{NONE, NEITHER}, {GOOD, ONE}, {GOOD, ONE}, {GOOD, ONE}, {GOOD, ONE}, {NONE, NEITHER}}};

        void modifyTileGhost(int x, int y, GhostState ghost)
        void modifyTilePlayer(int x, int y, PlayerState player)
};
