#include "BearLibTerminal.h"

#include "RootTerminal.h"
#include "fmt/format.h"
RootTerminal::RootTerminal(std::string name)
: Terminal(name, 0, 0, TERMINAL_DEFAULT_WIDTH, TERMINAL_DEFAULT_HEIGHT)
{
    RootTerminal(name, TERMINAL_DEFAULT_WIDTH, TERMINAL_DEFAULT_HEIGHT);
}

RootTerminal::RootTerminal(std::string name, int width, int height)
: Terminal(name, 0, 0, width, height)
{   
    terminal_open();
    terminal_set(fmt::format("window: title='{}', size={}x{};", name, width, height).c_str());
    terminal_set("font: terminal_8x8.png, size=8x8;");
    terminal_refresh();
}

