enum GhostState { NONE, GOOD, BAD };
enum PlayerState { NONE, ONE, TWO };

struct Tile;
{
    GhostState ghostState;
    PlayerState playerState;
}
