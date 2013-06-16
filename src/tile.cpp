#include "tile.h"

//public
Tile TileGrid::getTileAt(int x, int y)
{
    return grid.at(y).at(x);
}

void TileGrid::moveSelectToSuggest()
{
    grid.at(suggestCoords.y).at(suggestCoords.x) = grid.at(selectCoords.y).at(selectCoords.x);
    grid.at(selectCoords.y).at(selectCoords.y) = {NEITHER, NONE};
    desuggestTile();
    deselectTile();
}

void TileGrid::setSelectedTile(int x, int y)
{
    selected = true;
    selectCoords = {x, y};
}

void TileGrid::setSuggestedTile(int x, int y)
{
    suggested = true;
    suggestCoords = {x, y};
}

Tile TileGrid::getSelectedTile()
{
    return grid.at(selectCoords.y).at(selectCoords.x);
}

Tile TileGrid::getSuggestedTile()
{
    return grid.at(suggestCoords.y).at(suggestCoords.x);
}

void TileGrid::deselectTile()
{
    selected = false;
    selectCoords = {-1, -1};
}

void TileGrid::desuggestTile()
{
    suggested = false;
    suggestCoords = {-1, -1};
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

bool TileGrid::isSelected()
{
    return selected;
}

TileCoords TileGrid::getSelectedCoords()
{
    return selectCoords;
}

TileCoords TileGrid::getSuggestedCoords()
{
    return suggestCoords;
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
