//
// Created by gil on 19/02/18.
//

#include "../include/chain.h"

using namespace boost::python;

AntibodyChainCPP::AntibodyChainCPP(std::string sequence, std::string name, std::string numbering_scheme) {

    aligned = false;

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
    chainObject = PyObject_CallFunction(Chain, "ssOs", sequence.c_str(), name.c_str(), Py_None,
                                        numbering_scheme.c_str());

    if (chainObject == nullptr) {
        std::cout << "Error instantiating object";
    }

}



AntibodyChainCPP::AntibodyChainCPP(const char &sequence, const char &name, const char &numbering_scheme) {

    aligned = false;

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


std::string AntibodyChainCPP::getAlignedSequence() {

    if (!alignedSequence) {
        std::cout << "Calling aligned_sequence" << "\n";
        auto* alignedSequenceArray = reinterpret_cast<PyArrayObject*>(PyObject_GetAttrString(chainObject,
                                                                                             "aligned_sequence"));

        // let boost handle PyObject memory allocation
        object temp(handle<>(alignedSequenceArray));

        auto arraySize = static_cast<int>(PyArray_DIMS(alignedSequenceArray)[0]);

        // build string from PyArray
//        alignedSequence = std::string(alignedSequenceChar);

        // initialise aligned_sequence
        alignedSequence = "";

        for (int j = 0; j < arraySize; ++j) {
            (*alignedSequence).append((char*) PyArray_GETPTR1(alignedSequenceArray, j));
        }

        std::cout << (*alignedSequence) << "\n";
    }

    return *alignedSequence;
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

    std::cout << "call getChain(): " << *chain << std::endl;

    return *chain;
}

std::vector<double> AntibodyChainCPP::getAminoAcidCharges(bool align, double pH, char *pka_database) {

    auto* chargePyObject = reinterpret_cast<PyArrayObject*>(PyObject_CallMethod(chainObject, "ab_charge", "ids", align,
                                                                                pH, pka_database));

    // let boost handle PyObject memory allocation
    object temp(handle<>(chargePyObject));

    auto arraySize = static_cast<int>(PyArray_DIMS(chargePyObject)[0]);

    auto chargeDouble = static_cast<double*>(PyArray_DATA(chargePyObject));

    std::vector<double> aminoAcidChargesVector(chargeDouble, chargeDouble + arraySize);

    return aminoAcidChargesVector;
}

std::vector<double> AntibodyChainCPP::getHydrophobicityMatrix(char *hydrophobicity_scores) {

    auto* hValuesPyObject = reinterpret_cast<PyArrayObject*>(PyObject_CallMethod(chainObject,
                                                                                 "ab_hydrophobicity_matrix",
                                                                                 "s", hydrophobicity_scores));

    // let boost handle PyObject memory allocation
    object temp(handle<>(hValuesPyObject));

    int arraySize = static_cast<int>(PyArray_DIMS(hValuesPyObject)[0]);

    auto hValuesDouble = static_cast<double*>(PyArray_DATA(hValuesPyObject));

    std::vector<double> aminoAcidHValues(hValuesDouble, hValuesDouble + arraySize);

    return aminoAcidHValues;
}


std::vector<double> AntibodyChainCPP::getHydrophobicityMatrix(hydrophobicityParser &customHValues_) {

    std::string replacementString = "-";

    if (!alignedSequence) {
        auto temp = getAlignedSequence();
    }

    auto oneLetterMap =  customHValues_.getAminoAcidHydrophobicityMap(1);

    std::vector<double> hValues;
    hValues.resize((*alignedSequence).length());

    for (int j = 0; j < hValues.size(); ++j) {

        if ((*alignedSequence).substr(j, 1).compare(0, 1, replacementString) == 0) {
            // this is a replacement string and has no amino acid value
            hValues[j] = 0;
        }
        else {
            hValues[j] = oneLetterMap[(*alignedSequence).substr(j, 1)];
        }

    }

    return hValues;
}

void AntibodyChainCPP::load() {

    if (!aligned) {
        try {
            PyObject_CallMethod(chainObject, "load", "");

        }
        catch (error_already_set &) {
            PyObject * pType, *pValue, *pTraceback;

            PyErr_Fetch(&pType, &pValue, &pTraceback);

            throw PythonAbPyToolsError(pType, pValue, pTraceback);
        }
    }

    std::cout << "call getChain() from load(): " << getChain() << std::endl;

    if (getChain() == "heavy" or getChain() == "light")
        aligned = true;
//    else
//        std::cout << getChain();
}

void AntibodyChainCPP::printSequence() {

    if (!sequence) {
        auto temp = getSequence();
    }

    std::cout << (*sequence);
}
