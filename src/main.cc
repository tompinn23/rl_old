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
#include <iostream>

#include "Python.h"

#include "BearLibTerminal.h"
#include "interface.h"
#include "generate.h"
#include "player.h"
#include "colors.h"

using namespace std;
void DrawMenu();
void drawMap(vector<tile> map, player Player);
void movePlayer(player &Player);
int main(int argc, char** argv)
{
	register_rooms();
	//read_rooms("data/surface/rooms.txt");
    terminal_open();
	terminal_set("font: terminal_8x8.png, size=8x8;");
    //DrawMenu();
    vector<tile> town = generate_surface();
    player Player = player(1, 1, "tom");
    while(true)
    {
        drawMap(town, Player);
        movePlayer(Player);
        terminal_refresh();
    }
    return 0;
}

void drawMap(vector<tile> map, player Player)
{
    //printf("here?");
    for(int i = 0; i < 60; i++)
    {
        for(int j = 0; j < 40; j++)
        {
            int map_x, map_y;
            tie(map_x, map_y) = Player.screen_transform(i, j);
            //out << map_x << "," << map_y << "\n";
            tile t = get_tile(map_x, map_y, map);
            switch(t)
            {
                case EMPTY:
                    terminal_put(i, j, ' ');
                    break;
                case ROAD:
                    terminal_put(i, j, '.');
                    break;
                case WALL:
                    terminal_put(i, j, '#');
                    break;
                case WATER:
                    terminal_color(LIGHT_BLUE);
                    terminal_put(i, j, '~');
                    terminal_color(WHITE);
                    break;
            }
        }
    }
}

void movePlayer(player &Player)
{
    if(terminal_has_input())
    {
        int k = terminal_read();
        if(k == TK_W)
            Player.move_player(0,-1);
        else if(k == TK_A)
            Player.move_player(-1,0);
        else if(k == TK_S)
            Player.move_player(0,1);
        else if(k == TK_D)
            Player.move_player(1,0);
    }
}


void DrawMenu()
{
    terminal_print(4, 4, "1) Start Game");
    terminal_print(4, 5, "2) Settings");
    terminal_print(4, 6, "3) Exit");
    terminal_refresh();
}