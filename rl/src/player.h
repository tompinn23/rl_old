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
#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <tuple>

namespace rl
{
	class player
	{
	public:
		player(int x, int y, std::string name);
		void move_player(int dx, int dy);
		std::tuple<int, int> screen_transform(int x, int y);
	private:
		int p_x = 0;
		int p_y = 0;
		std::string name;

		int camera_width = 60;
		int camera_height = 40;

	};
}
#endif