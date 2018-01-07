#include <iostream>

#include "BearLibTerminal.h"

void DrawMenu();

int main(int argc, char** argv)
{
    terminal_open();
    DrawMenu();
    whi
    return 0;
}


void DrawMenu()
{
    terminal_print(4, 4, "1) Start Game");
    terminal_print(4, 5, "2) Settings");
    terminal_print(4, 6, "3) Exit");
    terminal_refresh();
}


