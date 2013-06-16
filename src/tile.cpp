#include "tile.h"

//public
Tile TileGrid::getTileAt(int x, int y) const
{
    return grid.at(y).at(x);
}

void TileGrid::moveSelectToSuggest()
{
    grid.at(suggestedCoords.y).at(suggestedCoords.x) = grid.at(selectedCoords.y).at(selectedCoords.x);
    grid.at(selectedCoords.y).at(selectedCoords.y).playerState = NEITHER;
    grid.at(selectedCoords.y).at(selectedCoords.y).ghostState = NONE;
    desuggestTile();
    deselectTile();
}

void TileGrid::setSelectedTile(int x, int y)
{
    selected = true;
    selectedCoords = {x, y};
}

void TileGrid::setSuggestedTile(int x, int y)
{
    suggested = true;
    suggestedCoords = {x, y};
}

Tile TileGrid::getSelectedTile() const
{
    return grid.at(selectedCoords.y).at(selectedCoords.x);
}

Tile TileGrid::getSuggestedTile() const
{
    return grid.at(suggestedCoords.y).at(suggestedCoords.x);
}

TileCoords TileGrid::getSelectedCoords() const
{
    return selectedCoords;
}

TileCoords TileGrid::getSuggestedCoords() const
{
    return suggestedCoords;
}

void TileGrid::deselectTile()
{
    selected = false;
    selectedCoords = {-1, -1};
}

void TileGrid::desuggestTile()
{
    suggested = false;
    suggestedCoords = {-1, -1};
}

bool TileGrid::withinGrid(int x, int y)
{
    return ((x <= 5 && x >= 0) && (y <= 5 && y >= 0));
}

bool TileGrid::surroundingSelectedTile(int x, int y)
{
    return (((x == selectedCoords.x + 1 || x == selectedCoords.x - 1) && y == selectedCoords.y)
        || ((y == selectedCoords.y + 1 || y == selectedCoords.y - 1) && x == selectedCoords.x));
}

bool TileGrid::isSuggested()
{
    return suggested;
}

bool TileGrid::isSelected()
{
    return selected;
}

//private
// lol do i even use these ever?
void TileGrid::modifyTileGhost(int x, int y, GhostState ghost)
{
    grid.at(y).at(x).ghostState = ghost;
}

void TileGrid::modifyTilePlayer(int x, int y, PlayerState player)
{
    grid.at(y).at(x).playerState = player;
}
