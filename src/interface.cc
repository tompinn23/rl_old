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
#include <cstdlib>
#include <cstdio>


#include "interface.h"
#include "whereami.h"
#include "spdlog/spdlog.h"

#include "portability.h"

#define _CRT_SECURE_NO_WARNINGS 1
using namespace std;

shared_ptr<spdlog::logger> rl_logger;

static PyObject* rl_room_declaration(PyObject* self, PyObject* args)
{
	room tempRoom;
	PyObject* room;
	if (!PyArg_ParseTuple(args, "O!", &PyDict_Type, &room))
		return NULL;
	PyObject* pyName = PyDict_GetItemString(room, "name");
	if(pyName != NULL)
	{
		PyObject* ascii_string = PyUnicode_AsASCIIString(pyName);
		char* name = PyBytes_AsString(ascii_string);
		string s = std::string(name);
		tempRoom.name = s;
	}
	else
	{
		rl_logger->error("Room Name was missing");
		return PyErr_Format(PyExc_KeyError, "%s", "Room name was missing from declaration");
	}
	PyObject* attrs = PyDict_GetItemString(room, "attrs");
	vector<string> vAttrs;
	tempRoom.attrs = vAttrs;
	if(attrs != NULL)
	{
		for(int i = 0; i < PyList_Size(attrs); i++)
		{
			PyObject* item = PyList_GetItem(attrs, i);
			PyObject* ascii_str = PyUnicode_AsASCIIString(item);
			char* sItem = PyBytes_AsString(ascii_str);
			vAttrs.push_back(string(sItem));
		}
		tempRoom.attrs = vAttrs;
	}
	PyObject* plan = PyDict_GetItemString(room, "plan");
	vector<tile> vPlan;
	if(plan != NULL)
	{
		for(int i = 0; i < PyList_Size(plan); i++)
		{
			PyObject* item = PyList_GetItem(plan, i);
			PyObject* ascii_str = PyUnicode_AsASCIIString(item);
			char* sItem = PyBytes_AsString(ascii_str);
			int j = 0;
			for (auto& c : string(sItem))
			{
				if (c == '#')
					place_tile(i, j, WALL, vPlan);
				else if (c == '.')
					place_tile(i, j, FLOOR, vPlan);
				else if (c == '~')
					place_tile(i, j, WATER, vPlan);
				else if (c == '=')
					place_tile(i, j, DOOR, vPlan);
				else if (c == ' ')
					place_tile(i, j, EMPTY, vPlan);
				j++;
			}
		}
		tempRoom.plan = vPlan;
	}
	else
	{
		rl_logger->error("Room plan was missing from declaration");
		return PyErr_Format(PyExc_KeyError, "%s", "Room plan was missing from declaration");
	}
	add_to_registry(tempRoom);
	Py_RETURN_NONE;
}

static PyMethodDef rl_methods[] = {
	{"decl_room", (PyCFunction)rl_room_declaration, METH_VARARGS, "Declare a room prototype."},
	{NULL, NULL, 0, NULL}
};

static struct PyModuleDef rl_module = {
	PyModuleDef_HEAD_INIT,
    "rl",
	NULL,
	-1,
	rl_methods,
	NULL,
	NULL,
	NULL,
	NULL
};

PyMODINIT_FUNC PyInit_rl()
{
	return PyModule_Create(&rl_module);
}

int initialise_interface(string &dir)
{
	rl_logger = spdlog::get("rl_logger");
	PyImport_AppendInittab("rl", PyInit_rl);
	rl_logger->info("Initialising Python");
	Py_Initialize();
	//PyImport_ImportModule("rl");
	return PyRun_SimpleString("import rl");
}

int deinitialise_interface()
{
	rl_logger->info("Deinitialising Python");
	return Py_FinalizeEx();
}