#ifndef INTERFACE_H
#define INTERFACE_H

#include <Python.h>

//Python Module

PyObject* rl_room_declaration(PyObject* self, PyObject* args);


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

PyMODINIT_FUNC PyInit_rl();


int register_rooms();

#endif