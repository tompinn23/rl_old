/*
    rl is a rougelike game.
    Copyright (C) 2018 Tom Pinnock

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
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

