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
#ifndef PORTABILITY_H
#define PORTABILITY_H

#include <vector>
#include <string>

typedef struct {
	bool isDirectory;
	std::string name;
} rl_file;

const std::string get_exe_dir();

const std::string get_path(std::string path);

std::vector<rl_file> list_files(std::string dir);

void add_handlers();
#endif