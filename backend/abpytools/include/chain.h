//
// Created by gil on 19/02/18.
//

#ifndef ABPYTOOLS_QT_CHAIN_H
#define ABPYTOOLS_QT_CHAIN_H

#include <Python.h>

class AntibodyChainCPP {

public:
    AntibodyChainCPP();
    ~AntibodyChainCPP();

private:
    const char module_name[10] = "abpytools";
    PyObject* module, *dict, *python_class, *object;

};

#endif //ABPYTOOLS_QT_CHAIN_H
