//
// Created by gil on 19/02/18.
//

#ifndef ABPYTOOLS_QT_CHAIN_H
#define ABPYTOOLS_QT_CHAIN_H

#include <Python.h>
#include <string>
#include <vector>
#include <boost/optional.hpp>

class AntibodyChainCPP {

public:
    AntibodyChainCPP() {}
    AntibodyChainCPP(char *sequence, char *name, char *numbering_scheme);
    ~AntibodyChainCPP();

    // GETTERS (gets python @property)
    std::string getName();
    std::string getSequence();
    std::string getNumberingScheme();
    std::string getChain();
    std::vector<double> getAminoAcidCharges(bool align, double pH, char *pka_database);

    // METHODS
    void load();

private:
    const char module_name[10] = "abpytools";
    PyObject* module, *chainObject;
    // using boost::optional reduces the number of calls to python by caching results
    // if attribute has already been requested by getter
    boost::optional<std::string> name;
    boost::optional<std::string> sequence;
    boost::optional<std::string> chain;
    boost::optional<std::string> numbering_scheme;
};

#endif //ABPYTOOLS_QT_CHAIN_H
