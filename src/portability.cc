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
#include "portability.h"

#include <algorithm>
#include <iostream>

#include "whereami.c"
#include "spdlog/spdlog.h"
#include "BearLibTerminal.h"

#if defined(WIN32) && !defined(__linux__)
#include <windows.h>
#elif defined(__linux__) && !defined(WIN32)

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <csignal>

#endif

#include "interface.h"
using namespace std;

string exe_dir;

fs::path get_exe_dir()
{
    if(!exe_dir.empty())
        return exe_dir;
    int length = wai_getExecutablePath(NULL, 0, NULL);
	char* path = (char*)malloc(length + 1);
	wai_getExecutablePath(path, length, NULL);
    string dir = string(path);
	dir = dir.substr(0, dir.find_last_of("."));
	dir = dir.substr(0, dir.size()-2);
    free(path);
    exe_dir = dir;
    return fs::path(exe_dir);
}

const string get_path(string path)
{
#if defined(WIN32) && !defined(__linux__)
    std::replace(path.begin(), path.end(), '/', '\\');
#elif defined(__linux__) && !defined(WIN32)
    std::replace(path.begin(), path.end(), '\\', '/');
#endif
    return path;
}

#if defined(WIN32) && !defined(__linux__)

std::vector<rl_file> list_files(std::string dir)
{
	vector<rl_file> files;
	dir.append("\\*");
	WIN32_FIND_DATA data;
	DWORD fAttrs;
	HANDLE hFind;
	if ((hFind = FindFirstFile(dir.c_str(), &data)) != INVALID_HANDLE_VALUE)
	{
		do {
			rl_file file;
			file.name = string(data.cFileName);
			fAttrs = GetFileAttributes(data.cFileName);
			if (fAttrs == INVALID_FILE_ATTRIBUTES)
				continue;
			if (fAttrs & FILE_ATTRIBUTE_DIRECTORY)
				file.isDirectory = true;
			else
				file.isDirectory = false;
			files.push_back(file);
		} while (FindNextFile(hFind, &data) != 0);
		FindClose(hFind);
	}
	return files;
}

//TODO: Implement signal  on windows.

static BOOL WINAPI ctrlhandler(DWORD ctrlType) {
	auto log = spdlog::get("rl_logger");
	deinitialise_interface();
	log->info("Exiting rl");
	return TRUE;
}

void add_handlers()
{
	//SetConsoleCtrlHandler((PHANDLER_ROUTINE)ctrlhandler, TRUE);
	//NOT WORKING!!!
}

#elif defined(__linux__) && !defined(WIN32)

std::vector<rl_file> list_files(std::string dir)
{
    vector<rl_file> files;
    DIR* dirp = opendir(dir.c_str());
    struct dirent* dp;
    while((dp = readdir(dirp)) != NULL)
    {
		struct stat sb;
		rl_file file;
		file.name = string(dp->d_name);
		if(stat(dp->d_name, &sb) == 0 && S_ISDIR(sb.st_mode))
			file.isDirectory = true;
		else
			file.isDirectory = false;
        files.push_back(file);
    }
    closedir(dirp);
	return files;
}

static void sigint_handler(int s)
{
	auto log = spdlog::get("rl_logger");
	deinitialise_interface();
	//terminal_close();
	log->info("Exiting rl");
	exit(1);
}

void add_handlers()
{
	signal(SIGINT, sigint_handler);
}

#endif
