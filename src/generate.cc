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

bool place_tile(int x, int y, tile Tile, vector<tile>& map)
{
	if (x < 0 || x > 255 || y < 0 || y > 255)
		return false;
    map[256 * y + x] = Tile;
	return true;
}

tile get_tile(int x, int y, vector<tile> map)
{
	if (x < 0 || x > 255 || y < 0 || y > 255)
		return WATER;
	return map.at(256 * y + x);
}

vector<tile> generate_surface()
{
    vector<tile> town = vector<tile>();
    town.resize(65536, EMPTY);
    place_tile(3, 4, WALL, town);
    place_tile(3, 3, WALL, town);
    return town;
}

