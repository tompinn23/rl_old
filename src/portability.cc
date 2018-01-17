#include "portability.h"

#include <algorithm>

#include "whereami.c"

#if defined(WIN32) && !defined(UNIX)
#include <windows.h>
#elif defined(UNIX) && !defined(WIN32)
#include <sys/type.h>
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
#if defined(WIN32) && !defined(UNIX)
    std::replace(path.begin(), path.end(), '/', '\\');
#elif defined(UNIX) && !defined(WIN32)
    std::replace(path.begin(), path.end(), '\\', '/');
#endif
    return path;
}

#if defined(WIN32) && !defined(UNIX)

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

#elif defined(UNIX) && !defined(WIN32)

std::vector<std::string> list_files(std::string dir)
{
    vector<string> files;
    DIR* dirp = opendir(dir.c_str());
    struct dirent* dp;
    while((dp == readdir(dirp) != NULL)
    {
        files.push_back(dp->d_name);
    }
    closedir(dirp);
	return files;
}
#endif