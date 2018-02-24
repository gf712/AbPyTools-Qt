//
// Created by gil on 19/02/18.
//

#include "chain.h"
#include "exception.h"

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

std::string AntibodyChainCPP::getName() {
    if (!name) {
        name = std::string(PyUnicode_AsUTF8(PyObject_GetAttrString(chainObject, "name")));
    }
    return *name;
}

std::string AntibodyChainCPP::getSequence() {
    if (!sequence) {
        sequence = PyUnicode_AsUTF8(PyObject_GetAttrString(chainObject, "sequence"));
    }
    return *sequence;
}

std::string AntibodyChainCPP::getNumberingScheme() {
    if (!numbering_scheme) {
        numbering_scheme = PyUnicode_AsUTF8(PyObject_GetAttrString(chainObject, "numbering_scheme"));
    }
    return *numbering_scheme;
}

std::string AntibodyChainCPP::getChain() {
    if (!chain) {
        chain = PyUnicode_AsUTF8(PyObject_GetAttrString(chainObject, "chain"));
    }
    return *chain;
}

std::vector<double> AntibodyChainCPP::getAminoAcidCharges(bool align, double pH, char *pka_database) {

    PyObject* chargePyObject = PyObject_CallMethod(chainObject, "ab_charge", "ids", align, pH, pka_database);

    // let boost handle PyObject memory allocation
    object temp(handle<>(chargePyObject));

    auto arraySize = static_cast<int>(PyArray_DIMS(chargePyObject)[0]);

    auto chargeDouble = static_cast<double*>(PyArray_DATA(chargePyObject));

    std::vector<double> aminoAcidChargesVector(chargeDouble, chargeDouble + arraySize);

    return aminoAcidChargesVector;
}

std::vector<double> AntibodyChainCPP::getHydrophobicityMatrix(char *hydrophobicity_scores) {

    PyObject* hValuesPyObject = PyObject_CallMethod(chainObject, "ab_hydrophobicity_matrix", "s", hydrophobicity_scores);

    // let boost handle PyObject memory allocation
    object temp(handle<>(hValuesPyObject));

    int arraySize = static_cast<int>(PyArray_DIMS(hValuesPyObject)[0]);

    auto hValuesDouble = static_cast<double*>(PyArray_DATA(hValuesPyObject));

    std::vector<double> aminoAcidHValues(hValuesDouble, hValuesDouble + arraySize);

    return aminoAcidHValues;
}


std::vector<double> AntibodyChainCPP::getHydrophobicityMatrix(hydrophobicityParser &customHValues_) {

    if (!sequence) {
        getSequence();
    }

    std::vector<double> hValues((*sequence).length());

    for (int j = 0; j < hValues.size(); ++j) {

        std::cout << hValues[j];

        customHValues_.getAminoAcidHydrophobicityMap()[(*sequence).substr(j)];

    }

}

void AntibodyChainCPP::load() {
    try {
        PyObject_CallMethod(chainObject, "load", "");

    }
    catch (error_already_set&) {
        PyObject *pType,*pValue,*pTraceback;

        PyErr_Fetch(&pType, &pValue, &pTraceback);

        throw PythonAbPyToolsError(pType, pValue, pTraceback);
    }
}
