#include "tile.h"

//public
void TileGrid::setTileAsSelected(int x, int y)
{
    selected = true;
    selectedX = x;
    selectedY = y;
}

void TileGrid::setTileAsSuggested(int x, int y)
{
    suggested = true;
    suggestedX = x;
    suggestedY = y;
}

void TileGrid::deselectTile()
{
    selected = false;
    selectedX = -1;
    selectedY = -1;
}

void TileGrid::desuggestTile()
{
    suggested = false;
    suggestedX = -1;
    suggestedY = -1;
}

bool TileGrid::withinGrid(int x, int y)
{
    return ((x <= 5 && x >= 0) && (y <= 5 && y >= 0));
}

bool TileGrid::surroundingSelectedTile(int x, int y)
{
    return (((x == selectedX + 1 || x == selectedX - 1) && y == selectedY)
        || ((y == selectedY + 1 || y == selectedY - 1) && x == selectedX));
}

bool TileGrid::isSuggested()
{
    return suggested;
}

//private
void TileGrid::modifyTileGhost(int x, int y, GhostState ghost)
{
    grid.at(y).at(x).ghostState = ghost;
}

void TileGrid::modifyTilePlayer(int x, int y, PlayerState player)
{
    grid.at(y).at(x).playerState = player;
}
