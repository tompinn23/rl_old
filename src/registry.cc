#include "registry.h"
std::vector<room> rooms;


using namespace std;

void add_to_registry(room room, bool surface)
{
	rooms.push_back(room);
}