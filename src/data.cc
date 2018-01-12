#include "data.h"

#include <fstream>
#include <iostream>
using namespace std;

vector<vector<tile>> read_rooms(string path)
{
	ifstream* file = new ifstream(path, ifstream::in);
	if (!file->is_open())
	{
		cout << "Bad File." << "\n";
		delete file;
		return vector<vector<tile>>();
	}
	char c = file->get();
	string room_name = "";
	while (file->good()) {
		if (c == '/')
		{
			c = file->get();
			if (c == '*')
			{
				c = file->get();
				while (file->good() && c != '*')
				{
					c = file->get(); 
				}
				c = file->get();
				c = file->get();
			}
		}
		else if(isdigit(c))
		{
			continue;
		}		
		else if(c == '#')
		{
			c = file->get();
			while(c != '\n')
			{
				room_name += c;
				c = file->get();
			}
			
		}
		cout << c;
		c = file->get();
	}
	cout << room_name << '\n';
	delete file;
	return vector<vector<tile>>();
}