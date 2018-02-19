//
// Created by gil on 19/02/18.
//

#include <Python.h>
#include "chain.h"
#include <iostream>

AntibodyChainCPP::AntibodyChainCPP() {

    Py_Initialize();
//    PySys_SetPath(L"/home/gil/anaconda3/lib/python3.6/site-packages/AbPyTools-0.1.1-py3.6.egg/");

    module = PyImport_ImportModule(module_name);
    if (module == nullptr) {
        PyErr_Print();
        std::cerr << "Fails to import the module.\n";
        return;
    }
    Py_DECREF(module_name);

}