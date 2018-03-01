//
// Created by gil on 19/02/18.
//

#ifndef ABPYTOOLS_QT_CHAIN_H
#define ABPYTOOLS_QT_CHAIN_H

//#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION

#include <Python.h>
#include <string>
#include <vector>
#include <boost/optional.hpp>
#include "../../parsers/include/hydrophobicityParser.h"
#include <numpy/arrayobject.h>
#include <iostream>
#include <iterator>



class AntibodyChainCPP {

public:
    AntibodyChainCPP() {aligned=false;}
    AntibodyChainCPP(std::string sequence, std::string name, std::string numbering_scheme);
    AntibodyChainCPP(char *sequence, char *name, char *numbering_scheme);
    ~AntibodyChainCPP() = default;

    // GETTERS (for python @property)
    std::string getName();
    std::string getSequence();
    std::string getAlignedSequence();
    std::string getNumberingScheme();
    std::string getChain();
    std::vector<double> getAminoAcidCharges(bool align, double pH, char *pka_database);
    std::vector<double> getHydrophobicityMatrix(char *hydrophobicity_scores);

    // SETTERS
    // can start object with empty initialisera and set values after
    void setName(std::string name_) {name = name_;}
    void setSequence(std::string sequence_) {sequence = sequence_;}
    void setNumberingScheme(std::string numbering_scheme_) {numbering_scheme = numbering_scheme_;}

    // C++ functions that do the same as AbPyTools
    // - reasoning: once the frontend has been build the user will be able to submit custom files
    //   which will be parsed with the C++ parsers. So it doesn't make sense to just send data
    //   back in forth from C++ to Python, and back, so let it all happen here!
    std::vector<double> getHydrophobicityMatrix(hydrophobicityParser &customHValues_);

    // METHODS
    void load();

    // LOGGING METHODS
    void printSequence();

private:
    const char module_name[10] = "abpytools";
    PyObject* module, *chainObject;
    // using boost::optional reduces the number of calls to python by caching results
    // if attribute has already been requested by getter
    boost::optional<std::string> name;
    boost::optional<std::string> sequence;
    boost::optional<std::string> chain;
    boost::optional<std::string> numbering_scheme;
    boost::optional<std::string> alignedSequence;
    bool aligned;
};

#endif //ABPYTOOLS_QT_CHAIN_H
