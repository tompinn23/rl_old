#ifndef INTERFACE_H
#define INTERFACE_H



#include <Python.h>
#include <string>
//Python Module





//int register_rooms();

//#include "duktape.h"
//#include "duk_config.h"

int initialise_interface(std::string dir);
int deinitialise_interface();


#endif