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
#endif