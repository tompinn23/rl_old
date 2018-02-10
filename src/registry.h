#ifndef REGISTRY_H
#define REGISTRY_H

#include <string>
#include <vector>

namespace rl
{
	typedef unsigned char tile;

	typedef struct {
		std::string name;
		std::vector<std::string> attrs;
		std::vector<tile> plan;
	} rl_room;



	void add_to_registry(rl_room room, bool surface);
	}
#endif // !REGISTRY_H
