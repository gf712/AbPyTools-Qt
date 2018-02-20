//
// Created by gil on 19/02/18.
//

#include <Python.h>
#include "chain.h"
#include <iostream>
#include "exception.h"

AntibodyChainCPP::AntibodyChainCPP(char *sequence, char *name, char *numbering_scheme) {

    Py_Initialize();

    module = PyImport_ImportModule(module_name);
    if (module == nullptr) {
        throw ModuleImportException(std::string("Could not import AbPyTools!"));
    }

    static PyObject* Chain = PyObject_GetAttrString(module, "Chain");

    if (Chain == nullptr) {
        throw ClassImportException(std::string("Could not import Chain class from abpytools!"));
    }
    else {
        Py_INCREF(Chain);
    }

    // now we can instantiate the python object
    chainObject = PyObject_CallFunction(Chain, "ssOs", sequence, name, Py_None, numbering_scheme);

    if (chainObject == nullptr) {
        std::cout << "Error instantiating object";
    }

}

char* AntibodyChainCPP::getName() {
    return PyUnicode_AsUTF8(PyObject_GetAttrString(chainObject, "name"));
}
