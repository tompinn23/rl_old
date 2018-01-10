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