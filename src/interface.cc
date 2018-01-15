// #include <Python.h>
#include <iostream>
#include "interface.h"
#include <cstdlib>
#include <cstdio>

#define _CRT_SECURE_NO_WARNINGS 1
#ifdef _WIN32_
#include <Windows.h>	
#endif

static PyObject* rl_room_declaration(PyObject* self, PyObject* args)
{
	PyObject* room;
	if (!PyArg_ParseTuple(args, "O!", &PyDict_Type, &room))
		return NULL;
	PyObject* pyName = PyDict_GetItemString(room, "name");
	PyObject* ascii_string = PyUnicode_AsASCIIString(pyName);
	char* name = PyBytes_AsString(ascii_string);
	std::string s = std::string(name);
	std::cout << s << "\n";
	if(PyDict_Contains(room, PyUnicode_FromString("attrs")))
	{
		std::cout << "ATTRS" << "\n";
		PyObject* attrs = PyDict_GetItemString(room, "attrs");
		for(int i = 0; i < PyList_Size(attrs); i++)
		{
			PyObject* item = PyList_GetItem(attrs, i);
			PyObject* ascii_str = PyUnicode_AsASCIIString(item);
			char* sItem = PyBytes_AsString(ascii_str);
			std::cout << sItem << "\n";
		}
	}
	PyObject* plan = PyDict_GetItemString(room, "plan");
	for(int i = 0; i < PyList_Size(plan); i++)
	{
		PyObject* item = PyList_GetItem(plan, i);
		PyObject* ascii_str = PyUnicode_AsASCIIString(item);
		char* sItem = PyBytes_AsString(ascii_str);
		std::cout << sItem << "\n";
	}
	
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

int initialize_interface()
{
	PyImport_AppendInittab("rl", PyInit_rl);
	Py_Initialize();
	PyRun_SimpleString("from rl import *");
	FILE *fd = fopen("./lib/game/surface/rooms.py", "r");
	if(fd == NULL)
	{
		std::cerr << "Could not find file" << "\n";
		return -1;
	}
	PyRun_SimpleFileEx(fd, "rooms.py", 1);
	return 0;
}