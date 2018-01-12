#include "data.h"

#include <fstream>
#include <iostream>
using namespace std;

vector<vector<tile>> read_rooms(string path)
{
	cout << "get called?" << "\n";
	ifstream* file = new ifstream(path, ifstream::in);
	if (!file->is_open())
	{
		cout << "Bad File." << "\n";
		delete file;
		return vector<vector<tile>>();
	}
	char c = file->get();
	while (file->good())
	{
		cout << c;
		c = file->get();
	}
	while (file->good()) {
		cout << c;
		if (c == '/')
		{
			c = file->get();
			cout << c;
			if (c == '*')
			{
				c = file->get();
				cout << c;
				while (file->good() && c != '*')
				{
					c = file->get(); 
					cout << c;
				}
				c = file->get();
			}
		}
		cout << c;
		c = file->get();
	}
	delete file;
	return vector<vector<tile>>();
}