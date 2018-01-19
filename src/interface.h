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
#ifndef INTERFACE_H
#define INTERFACE_H



#include <string>
#include <vector>

#include "generate.h"
//Python Module

//int register_rooms();

//#include "duktape.h"
//#include "duk_config.h"

int initialise_interface(std::string &dir);
int deinitialise_interface();


#endif