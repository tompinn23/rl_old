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
#ifndef GENERATE_H
#define GENERATE_H

#include <vector>


#define EMPTY 0
#define FLOOR 1
#define WALL 2
#define WATER 3
#define DOOR 4



typedef unsigned char tile;

bool place_tile(int x, int y, tile Tile, std::vector<tile>& map);
tile get_tile(int x, int y, std::vector<tile> map);
std::vector<tile> generate_surface();




#endif