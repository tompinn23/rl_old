#include "registry.h"



using namespace std;
namespace rl
{
	static vector<rl_room> rooms;
	
	void add_to_registry(rl_room room, bool surface)
	{
		rooms.push_back(room);
	}
}