// #include <Python.h>
#include <iostream>
#include <cstdlib>
#include <cstdio>


#include "interface.h"
#include "whereami.h"
#include "spdlog/spdlog.h"

#define _CRT_SECURE_NO_WARNINGS 1
using namespace std;

shared_ptr<spdlog::logger> rl_logger;

static PyObject* rl_room_declaration(PyObject* self, PyObject* args)
{
	PyObject* room;
	if (!PyArg_ParseTuple(args, "O!", &PyDict_Type, &room))
		return NULL;
	PyObject* pyName = PyDict_GetItemString(room, "name");
	if(pyName != NULL)
	{
		PyObject* ascii_string = PyUnicode_AsASCIIString(pyName);
		char* name = PyBytes_AsString(ascii_string);
		string s = std::string(name);
		cout << s << "\n";
	}
	else
	{
		rl_logger->error("Room Name was missing");
		return PyErr_Format(PyExc_KeyError, "%s", "Room name was missing from declaration");
	}
	PyObject* attrs = PyDict_GetItemString(room, "attrs");
	if(attrs != NULL)
	{
		std::cout << "ATTRS" << "\n";
		for(int i = 0; i < PyList_Size(attrs); i++)
		{
			PyObject* item = PyList_GetItem(attrs, i);
			PyObject* ascii_str = PyUnicode_AsASCIIString(item);
			char* sItem = PyBytes_AsString(ascii_str);
			std::cout << sItem << "\n";
		}
	}
	PyObject* plan = PyDict_GetItemString(room, "plan");
	if(plan != NULL)
	{
		for(int i = 0; i < PyList_Size(plan); i++)
		{
			PyObject* item = PyList_GetItem(plan, i);
			PyObject* ascii_str = PyUnicode_AsASCIIString(item);
			char* sItem = PyBytes_AsString(ascii_str);
			std::cout << sItem << "\n";
		}
	}
	else
		return PyErr_Format(PyExc_KeyError, "%s", "Room plan was missing from declaration");
	
	Py_RETURN_NONE;
}

static PyMethodDef rl_methods[] = {
	{"decl_room", rl_room_declaration, METH_VARARGS, "Declare a room prototype."}
};

static struct PyModuleDef rl_module = {
	PyModuleDef_HEAD_INIT,
    "rl",
	NULL,
	-1,
	rl_methods
};

PyMODINIT_FUNC PyInit_rl()
{
	return PyModule_Create(&rl_module);
}

/* 
int register_rooms()
{
	PyObject *pName, *pModule, *pDict, *pFunc;
	PyObject *pArgs, *pValue;
	int i;
	
	PyImport_AppendInittab("rl", PyInit_rl);
	Py_Initialize();
	PyObject *sys = PyImport_ImportModule("sys");
	PyObject *path = PyObject_GetAttrString(sys, "path");
	PyList_Append(path, PyUnicode_FromString("."));
	PyList_Append(path, PyUnicode_FromString("C:"));

	PyImport_ImportModule("rl");
	pName = PyUnicode_DecodeFSDefault("C:/data/surface/rooms");
	std::cout << PyUnicode_AsASCIIString(pName);
	pModule = PyImport_ImportModule("data/surface/rooms");
	if (pModule == NULL)
		return -1;
	Py_DECREF(pName);
	Py_DECREF(pModule);
	return 0;
}
*/

int initialize_interface(string dir)
{
	rl_logger = spdlog::get("rl_logger");
	PyImport_AppendInittab("rl", PyInit_rl);
	Py_Initialize();
	PyRun_SimpleString("from rl import *");
	string libPath = "/lib/game/surface/rooms.py";
	string file = dir + libPath;
	FILE *fd = fopen(file.c_str(), "r");
	if(fd == NULL)
	{
		std::cerr << "Could not find file" << "\n";
		return -1;
	}
	return PyRun_SimpleFileEx(fd, file.c_str(), 1);
}