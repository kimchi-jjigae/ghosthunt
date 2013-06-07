enum GhostState { NONE, GOOD, BAD };
enum PlayerState { NEITHER, ONE, TWO };

struct Tile
{
    GhostState ghostState;
    PlayerState playerState;
};
