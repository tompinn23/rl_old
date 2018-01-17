// #include <Python.h>
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

char *PyTraceback_AsString(PyObject *exc_tb)
{
	char *errMsg = NULL; /* holds a local error message */
	char *result = NULL; /* a valid, allocated result. */
	PyObject *modStringIO = NULL;
	PyObject *modTB = NULL;
	PyObject *obFuncStringIO = NULL;
	PyObject *obStringIO = NULL;
	PyObject *obFuncTB = NULL;
	PyObject *argsTB = NULL;
	PyObject *obResult = NULL;

	/* Import the modules we need - cStringIO and traceback */
	modStringIO = PyImport_ImportModule("cStringIO");
	if (modStringIO==NULL)
	{
		rl_logger->error("cant import cStringIO");
		return NULL;
	}
	modTB = PyImport_ImportModule("traceback");
	if (modTB==NULL)
	{
		rl_logger->error("cant import traceback");
		return NULL;
	}
	/* Construct a cStringIO object */
	obFuncStringIO = PyObject_GetAttrString(modStringIO, "StringIO");
	if (obFuncStringIO==NULL)
	{
		rl_logger->error("cant find cStringIO.StringIO");
		return NULL;
	}
	obStringIO = PyObject_CallObject(obFuncStringIO, NULL);
	if (obStringIO==NULL)
	{
		rl_logger->error("cStringIO.StringIO() failed");
		return NULL;
	}
	/* Get the traceback.print_exception function, and call it. */
	obFuncTB = PyObject_GetAttrString(modTB, "print_tb");
	if (obFuncTB==NULL)
	{
		rl_logger->error("cant find traceback.print_tb");
		return NULL;
	}
	argsTB = Py_BuildValue("OOO", 
			exc_tb  ? exc_tb  : Py_None,
			Py_None, 
			obStringIO);
	if (argsTB==NULL)
	{
		rl_logger->error("cant make print_tb arguments");
		return NULL;
	}
	obResult = PyObject_CallObject(obFuncTB, argsTB);
	if (obResult==NULL) 
	{
		rl_logger->error("traceback.print_tb() failed");
	}
	/* Now call the getvalue() method in the StringIO instance */
	Py_DECREF(obFuncStringIO);
	obFuncStringIO = PyObject_GetAttrString(obStringIO, "getvalue");
	if (obFuncStringIO==NULL)
	{
		rl_logger->error("cant find getvalue function");
		return NULL;
	}
	Py_DECREF(obResult);
	obResult = PyObject_CallObject(obFuncStringIO, NULL);
	if (obResult==NULL) 
	{
		rl_logger->error("getvalue() failed.");
		return NULL;				
	}
	/* And it should be a string all ready to go - duplicate it. */
	if (!PyUnicode_Check(obResult))
	{		
		rl_logger->error("getvalue() did not return a string");
		return NULL;
	}
	{ // a temp scope so I can use temp locals.
	PyObject *temp = PyUnicode_AsASCIIString(obResult);
	char* tempResult = PyBytes_AsString(temp);
	result = (char *)PyMem_Malloc(strlen(tempResult)+1);
	if (result==NULL)
	{
		rl_logger->error("memory error duplicating the traceback string");
		return NULL;
	}
	strcpy(result, tempResult);
	} // end of temp scope.
	Py_XDECREF(modStringIO);
	Py_XDECREF(modTB);
	Py_XDECREF(obFuncStringIO);
	Py_XDECREF(obStringIO);
	Py_XDECREF(obFuncTB);
	Py_XDECREF(argsTB);
	Py_XDECREF(obResult);
	return result;
}



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
	{
		rl_logger->error("Room plan was missing from declaration");
		return PyErr_Format(PyExc_KeyError, "%s", "Room plan was missing from declaration");
	}
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

int initialise_interface(string dir)
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
	return Py_FinalizeEx();
}