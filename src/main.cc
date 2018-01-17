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
#include "main.h"

#include <iostream>
#include <fstream>

#include "BearLibTerminal.h"

#include "whereami.h"
#include "format.h"
#include "spdlog/spdlog.h"


#include "interface.h"
#include "generate.h"
#include "player.h"
#include "colors.h"
#include "portability.h"

#define RL_VERSION "1.0.0"

using namespace std;
namespace spd = spdlog;
string dir;
static bool closed_flag = false;


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
		if(k == TK_CLOSE)
        {
			terminal_close();
            closed_flag = true;
        }
        else if(k == TK_W)
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

std::shared_ptr<spd::logger> init_logger()
{
    std::vector<spdlog::sink_ptr> sinks;
    sinks.push_back(std::make_shared<spdlog::sinks::stdout_sink_mt>());
    sinks.push_back(std::make_shared<spdlog::sinks::rotating_file_sink_mt>("rl.log", 1048576 * 3, 3));
    auto rl_log = std::make_shared<spd::logger>("rl_logger", begin(sinks), end(sinks));
	auto file_log = std::make_shared<spd::logger>("rl_file_logger", sinks[1]);
    spd::register_logger(rl_log);
    return rl_log;
}

int main(int argc, wchar_t** argv)
{
    get_exe_dir();
	for (auto &v : list_files(get_exe_dir()))
	{
		if (v.isDirectory)
			cout << "DIR:" << v.name << "\n";
		else
			cout << "FILE:" << v.name << "\n";
	}
    auto logger = init_logger();
    spd::set_pattern("(%l) [%H:%M:%S %d/%m/%C] %v");
    logger->info("Rl v{}", RL_VERSION);
    if(initialise_interface(get_exe_dir()) == -1)
	{
		logger->error("Failed to read game data files.");
        return -1;
	}
    terminal_open();
	terminal_set(fmt::format("font: {}, size=8x8;", get_exe_dir() + "/terminal_8x8.png").c_str());
	terminal_refresh();
    //DrawMenu();
    vector<tile> town = generate_surface();
    player Player = player(1, 1, "tom");
    while(true && !closed_flag)
    {
        drawMap(town, Player);
        movePlayer(Player);
        terminal_refresh();
    }
    deinitialise_interface();
    return 0;
}

