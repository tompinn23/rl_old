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
#include <iostream>
#include "sol.hpp"
//#include <Python.h>

#include "interface.h"
#include "spdlog/spdlog.h"

#include "portability.h"
#include "registry.h"

#define _CRT_SECURE_NO_WARNINGS 1
using namespace std;

namespace rl
{
	shared_ptr<spdlog::logger> rl_logger;
	sol::state lua;
	
	sol::protected_function_result err_handler(lua_State* L, sol::protected_function_result pfr)
	{
		sol::error err = pfr;
		rl_logger->error(err.what());
		return pfr;
	}

	bool c_decl_room(sol::this_state s, sol::table room_table)
	{

		lua_State* L = s;
		lua_Debug info;
		lua_getstack(L, 1, &info);
		lua_getinfo(L, "nSl", &info);
		/*
			'n': fills in the field name and namewhat;
			'S': fills in the fields source, short_src, linedefined, lastlinedefined, and what;
			'l': fills in the field currentline; 
			short_src = filename;
		*/
		rl_logger->debug("Room declaration at {}:{}", info.short_src, info.currentline);
		bool missing = false;
		sol::optional<string> name = room_table["name"];
		sol::optional<string> desc = room_table["desc"];
		sol::optional<sol::table> attrs = room_table["attrs"];
		sol::optional<sol::table> plan = room_table["plan"];
		int count = room_table.size();
		cout << count;
		for(int i = 1; i <= count; ++i)
			cout << room_table[i].get<string>() << "\n" << i << "\n";
		if(name)
			rl_logger->debug(name.value());
		else
		{
			rl_logger->error("Room Name does not exist for declaration at {}:{}", info.short_src, info.currentline);
			missing = true;
		}
		if(desc)
		{
			rl_logger->debug(desc.value());
		}
		else
		{
			rl_logger->error("Room Description does not exist for declaration at {}:{}", info.short_src, info.currentline);
			missing = true;
		}
		if(attrs)
		{
			
		}
		
		return true;
	}

	int initialise_interface(string &dir)
	{
		rl_logger = spdlog::get("rl_logger");
		lua.open_libraries(sol::lib::base);
		rl_logger->debug("Initiating Lua State.");
		lua.set("decl_room", c_decl_room);
		return 0;
	}

// int deinitialise_interface()
// {
	// rl_logger->info("Deinitialising Python");
	// Py_Finalize();
	// return 0;
// }

	int run_file(fs::path file)
	{
		rl_logger->debug("Opening file {}", file.string());
		return lua.safe_script_file(file.string(), err_handler);
	}
}