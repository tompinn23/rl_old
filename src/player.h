#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <tuple>

class player
{
public:
    player(int x, int y, std::string name);
    void move_player(int dx, int dy);
    void move_left();
    void move_right();
    void move_up();
    void move_down();
    std::tuple<int, int> screen_transform(int x, int y);
private:
    int p_x = 0;
    int p_y = 0;
    std::string name;

    int camera_width = 60;
    int camera_height = 40;

};

#endif