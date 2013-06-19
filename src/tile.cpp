#include "tile.h"

//public
Tile TileGrid::getTileAt(int x, int y) const
{
    return grid.at(y).at(x);
}

void TileGrid::moveSelectToSuggest()
{
    grid.at(suggestedCoords.y).at(suggestedCoords.x) = grid.at(selectedCoords.y).at(selectedCoords.x);
    grid.at(selectedCoords.y).at(selectedCoords.x).playerState = NEITHER;
    grid.at(selectedCoords.y).at(selectedCoords.x).ghostState = NONE;
    desuggestTile();
    deselectTile();
}

void TileGrid::swapSelectAndSuggest()
{
    Tile tmp = grid.at(suggestedCoords.y).at(suggestedCoords.x);
    grid.at(suggestedCoords.y).at(suggestedCoords.x) = grid.at(selectedCoords.y).at(selectedCoords.x);
    grid.at(selectedCoords.y).at(selectedCoords.x) = tmp;
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

void TileGrid::placeEnemyGhosts(std::string enemyState)
{
    std::cout << "the string i'm _receiving_ is: " << enemyState << "\n";
    int k = 7;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 1; j < 5; j++)
        {
            if (k >= 0)
            {
                grid.at(i).at(j).playerState = TWO;
                if (enemyState[k] == 'G')
                {
                    grid.at(i).at(j).ghostState = GOOD;
                }
                else if (enemyState[k] == 'B')
                {
                    grid.at(i).at(j).ghostState = BAD;
                }
                else
                {
                    std::cout << "somethings wrong with the string lol\n";
                }
                k--;
            }
        }
    }
}

bool TileGrid::checkIfSetupValid()
{
    for (int i = 4; i < 6; i++)
    {
        for (int j = 1; j < 5; j++)
        {
            if (!(grid.at(i).at(j).playerState == ONE))
            {
                return false;
            }
        }
    }
    return true;
}

sf::Packet TileGrid::convertPositionsToPacket()
{
    sf::Packet paketti;
    std::string s = "";
    for (int i = 4; i < 6; i++)
    {
        for (int j = 1; j < 5; j++)
        {
            if (grid.at(i).at(j).ghostState == GOOD)
            {
                s += 'G';
            }
            else if (grid.at(i).at(j).ghostState == BAD)
            {
                s += "B";
            }
        }
    }
    std::cout << "the string i'm sending is: " << s << "\n";
    paketti << s;
    return paketti;
}

sf::Packet TileGrid::convertMoveToPacket()
{
    sf::Packet paketti;
    std::string s;
    if (grid.at(selectedCoords.y).at(selectedCoords.x).ghostState == GOOD)
    {
        s = "G";
    }
    else if (grid.at(selectedCoords.y).at(selectedCoords.x).ghostState == BAD)
    {
        s = "B";
    }
    paketti << suggestedCoords.x << suggestedCoords.y << selectedCoords.x << selectedCoords.y << s;
    std::cout << "filling the paketti with: " << suggestedCoords.x << " and " << suggestedCoords.y << " and " << selectedCoords.x << " and " << selectedCoords.y << " and " << s << "\n";
    return paketti;
}

void TileGrid::placeMove(sf::Packet paketti)
{
    int x1, y1, x2, y2;
    std::string s;
    paketti >> x2 >> y2 >> x1 >> y1 >> s;

    std::cout << "from inside the paketti, reading it as: " << x1 << " and " << y1 << " and " << x2 << " and " << y2 << " and " << s << "\n";

    x1 = 5 - x1;
    y1 = 5 - y1;
    x2 = 5 - x2;
    y2 = 5 - y2;

    std::cout << "after transforming from inside the paketti, reading it as: " << x1 << " and " << y1 << " and " << x2 << " and " << y2 << " and " << s << "\n";

    if (grid.at(y2).at(x2).ghostState == GOOD)
    {
        p1GoodGhostAmount--;
    }
    else if (grid.at(y2).at(x2).ghostState == BAD)
    {
        p1BadGhostAmount--;
    }

    if (s == "G")
    {
        grid.at(y2).at(x2).ghostState = GOOD;
        std::cout << "\n\ngood good good\n\n\n";
    }
    else if (s == "B")
    {
        grid.at(y2).at(x2).ghostState = BAD;
        std::cout << "\n\nbääääääääääääääääd\n\n\n";
    }
    else
    {
        std::cout << "soemthings wrong with the packet\n";
    }
    std::cout << "just before setting the player and ghost states from inside the paketti, reading it as: " << x1 << " and " << y1 << " and " << x2 << " and " << y2 << " and " << s << "\n";
    grid.at(y2).at(x2).playerState = TWO;
    grid.at(y1).at(x1).playerState = NEITHER;
    grid.at(y1).at(x1).ghostState = NONE;
}
