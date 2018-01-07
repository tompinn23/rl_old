#ifndef TERMINAL_H
#define TERMINAL_H

#include <string>
#include <vector>

#define TERMINAL_DEFAULT_WIDTH 80
#define TERMINAL_DEFAULT_HEIGHT 25

class Cell
{
public:
    Cell(int x, int y, char c)
    : x(x), y(y), c(c) {};


    int x;
    int y;
    char c;
};


class Terminal
{
public:
    Terminal(std::string name, int w, int h);
    Terminal(std::string name, int x, int y, int w, int h);
    void Put(int x, int y, char c);
    void Print(int x, int y, std::string s);
    void SetFgColour(uint8_t alpha, uint8_t red, uint8_t green, uint8_t blue);
    void SetBgColour(uint8_t alpha, uint8_t red, uint8_t green, uint8_t blue);
    void Blit(Terminal dest);
private:
    std::string name;
    int x = 0;
    int y = 0;
    int width;
    int height;
    std::vector<Cell> 
};




#endif