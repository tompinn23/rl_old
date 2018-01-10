#ifndef GENERATE_H
#define GENERATE_H

#include <vector>

#define EMPTY 0
#define ROAD 1
#define WALL 2
#define WATER 3

typedef unsigned char tile;

void place_tile(int x, int y, tile Tile, std::vector<tile>& map);
tile get_tile(int x, int y, std::vector<tile> map);
std::vector<tile> generate_surface();



#endif