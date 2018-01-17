#include "portability.h"

#include <algorithm>
#include <iostream>

#include "whereami.c"

#if defined(WIN32) && !defined(__linux__)
#include <windows.h>
#elif defined(__linux__) && !defined(WIN32)
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#endif
using namespace std;

string exe_dir;

const string get_exe_dir()
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
    return exe_dir;
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
#endif