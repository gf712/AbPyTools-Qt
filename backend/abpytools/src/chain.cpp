//
// Created by gil on 19/02/18.
//

#include <Python.h>
#include "chain.h"
#include <iostream>
#include "exception.h"
#include <boost/python.hpp>
using namespace boost::python;

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

    // now we can instantiate the python object
    chainObject = PyObject_CallFunction(Chain, "ssOs", sequence, name, Py_None, numbering_scheme);

    if (chainObject == nullptr) {
        std::cout << "Error instantiating object";
    }

}

char* AntibodyChainCPP::getName() {
    return PyUnicode_AsUTF8(PyObject_GetAttrString(chainObject, "name"));
}

char *AntibodyChainCPP::getSequence() {
    return PyUnicode_AsUTF8(PyObject_GetAttrString(chainObject, "sequence"));
}

char *AntibodyChainCPP::getNumberingScheme() {
    return PyUnicode_AsUTF8(PyObject_GetAttrString(chainObject, "numbering_scheme"));
}

void AntibodyChainCPP::load() {
    try {
        PyObject_CallMethod(chainObject, "load", "");

    }
    catch (error_already_set&) {
//        PyObject *exc,*val,*tb;
//

//        PyObject *pType, *pValue, *pTraceback;
//
//        PyErr_Fetch(&pType, &pValue, &pTraceback);
//
//        handle<> hType(pType);
//        object extype(hType);
//        handle<> hTraceback(pTraceback);
//        object traceback(hTraceback);
//
//        string strErrorMessage = extract<string>(pValue);
//
//        long lineno = extract<long> (traceback.attr("tb_lineno"));
//        string filename = extract<string>(traceback.attr("tb_frame").attr("f_code").attr("co_filename"));
//        string funcname = extract<string>(traceback.attr("tb_frame").attr("f_code").attr("co_name"));

//        throw
    }
}
