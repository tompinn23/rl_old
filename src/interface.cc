// #include <Python.h>
// #include <iostream>
// #include "interface.h"

// PyObject* rl_room_declaration(PyObject* self, PyObject* args)
// {
	// PyDictObject* room;
	// if (!PyArg_ParseTuple(args, "o", room))
		// return NULL;
	// std::cout << "HELLO FROM PYTHON" << "\n";
// }

// PyMODINIT_FUNC PyInit_rl()
// {
	// return PyModule_Create(&rl_module);
// }

// int register_rooms()
// {
	// PyObject *pName, *pModule, *pDict, *pFunc;
	// PyObject *pArgs, *pValue;
	// int i;
	
	// PyImport_AppendInittab("rl", PyInit_rl);
	// Py_Initialize();
	// PyObject *sys = PyImport_ImportModule("sys");
	// PyObject *path = PyObject_GetAttrString(sys, "path");
	// PyList_Append(path, PyUnicode_FromString("."));
	// PyList_Append(path, PyUnicode_FromString("C:"));

	// PyImport_ImportModule("rl");
	//pName = PyUnicode_DecodeFSDefault("C:/data/surface/rooms");
	//std::cout << PyUnicode_AsASCIIString(pName);
	// pModule = PyImport_ImportModule("data/surface/rooms");
	// if (pModule == NULL)
		// return -1;
	//Py_DECREF(pName);
	// Py_DECREF(pModule);
	// return 0;
// }