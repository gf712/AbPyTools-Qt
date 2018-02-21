//
// Created by gil on 19/02/18.
//

#ifndef ABPYTOOLS_QT_CHAIN_H
#define ABPYTOOLS_QT_CHAIN_H

#include <Python.h>
#include <string>
#include <vector>
using namespace std;

class AntibodyChainCPP {

public:
    AntibodyChainCPP() {}
    AntibodyChainCPP(char *sequence, char *name, char *numbering_scheme);
    ~AntibodyChainCPP();

    // GETTERS (gets python @property)
    char* getName();
    char* getSequence();
    char* getNumberingScheme();
    char* getChain();
    std::vector<double> getAminoAcidCharges(bool align, double pH, char *pka_database);

    // METHODS
    void load();

private:
    const char module_name[10] = "abpytools";
    PyObject* module, *chainObject;

};

#endif //ABPYTOOLS_QT_CHAIN_H
