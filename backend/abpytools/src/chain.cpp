//
// Created by gil on 19/02/18.
//

#include <Python.h>
#include "chain.h"
#include <iostream>
#include "exception.h"

AntibodyChainCPP::AntibodyChainCPP() {

    Py_Initialize();

    module = PyImport_ImportModule(module_name);
    if (module == nullptr) {
        throw ModuleImportException(std::string("Could not import AbPyTools!"));
    }
    Py_DECREF(module_name);

}