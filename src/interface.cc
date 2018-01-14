// #include <Python.h>
#include <iostream>
#include "interface.h"
#include <cstdlib>

static PyObject* rl_room_declaration(PyObject* self, PyObject* args)
{
	PyDictObject* room;
	if (!PyArg_ParseTuple(args, "O!", &PyDict_Type, &room))
		return NULL;
	
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
	SSSS
	return 0;
}