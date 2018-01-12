#include <Python.h>

#include "interface.h"

static PyObject* rl_room_declaration(PyObject* self, PyObject* args)
{
	PyDictObject* room;
	if (!PyArg_ParseTuple(args, "o", room))
		return NULL;
	
}

int register_rooms()
{
	PyObject *pName, *pModule, *pDict, *pFunc;
	PyObject *pArgs, *pValue;
	int i;
	
	Py_Initialize();
	pName = PyUnicode_DecodeFSDefault("data/surface/rooms.py")
	pModule = PyImport_Import(pName);
	
}