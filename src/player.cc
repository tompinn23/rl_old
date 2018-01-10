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

#include "player.h"


player::player(int x, int y, std::string name)
: p_x(x), p_y(y), name(name)
{

}

void player::move_down()
{
    std::cout << p_x << "," << p_y << "\n";
    p_y++;
    std::cout << p_x << "," << p_y << "\n";
}

void player::move_up()
{
    std::cout << p_x << "," << p_y << "\n";
    p_y--;
    std::cout << p_x << "," << p_y << "\n";
}

void player::move_left()
{
    std::cout << p_x << "," << p_y << "\n";
    p_x--;
    std::cout << p_x << "," << p_y << "\n";
}

void player::move_right()
{
    std::cout << p_x << "," << p_y << "\n";
    p_x++;
    std::cout << p_x << "," << p_y << "\n";
}

void player::move_player(int dx, int dy)
{
    std::cout << p_x << "," << p_y << "\n";
    p_x += dx;
    p_y += dy;
    std::cout << p_x << "," << p_y << "\n";
}

std::tuple<int, int> player::screen_transform(int x, int y)
{
    int cam_p_x = p_x - (camera_width / 2);
    int cam_p_y = p_y - (camera_height / 2);
    return std::make_tuple(cam_p_x + x, cam_p_y + y);
}