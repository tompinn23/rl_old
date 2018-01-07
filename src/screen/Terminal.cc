#include <string>

#include "BearLibTerminal.h"

#include "Terminal.h"

using ::std::string;

Terminal::Terminal(string name, int w, int h)
{
    this->name = name;
    width = w;
    height = h;
}

Terminal::Terminal(string name, int x, int y, int w, int h)
{
    this->name = name;
    this->x = x;
    this->y = y;
    width = w;
    height = h;
}

void Terminal::Put(int x, int y, char c)
{
    
}
