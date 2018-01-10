#include <vector>
#include <stdexcept>

#include "generate.h"

using namespace std;

void place_tile(int x, int y, tile Tile, vector<tile>& map)
{
    map[256 * y + x] = Tile;
}

tile get_tile(int x, int y, vector<tile> map)
{
    try
    {
        return map.at(256 * y + x);
    }
    catch(const out_of_range &err)
    {
        return WATER;
    }
}

vector<tile> generate_surface()
{
    vector<tile> town = vector<tile>();
    town.resize(65536, EMPTY);
    place_tile(3, 4, ROAD, town);
    place_tile(3, 3, ROAD, town);
    return town;
}

