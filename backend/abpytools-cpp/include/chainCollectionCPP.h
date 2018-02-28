//
// Created by gil on 21/02/18.
//

#ifndef ABPYTOOLS_QT_CHAINCOLLECTIONCPP_H
#define ABPYTOOLS_QT_CHAINCOLLECTIONCPP_H

#include <vector>
#include <string>
#include "chain.h"
#include "chainCollectionCPP.h"
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/optional.hpp>

using namespace boost::numeric::ublas;

class ChainCollectionCPP {
// This is a class containing CPP wrappers of the Chain python object
// The idea of this class is that once the chain objects are all loaded
// into the C++ wrapper it will be quicker to perform all the
// analysis with C++ rather than the already implemented python code

public:
    // CONSTRUCTORS
    ChainCollectionCPP();
    ChainCollectionCPP(std::vector<AntibodyChainCPP> antibodyObjects);
    ChainCollectionCPP(char* path, char* numberingScheme);
    ~ChainCollectionCPP() = default;

    // METHODS
    void load();
    void append(AntibodyChainCPP &AntibodyObject_);
    void updateAntibodyObjectVector(AntibodyChainCPP antibodyObject);

    // GETTERS
    template <typename T>
    T genericGetter(boost::optional<T>);

    std::vector<std::string> getNames() {return genericGetter<std::vector<std::string>>(names);}
    std::vector<std::string> getSequences() {return genericGetter<std::vector<std::string>>(sequences);}
    std::string getChainType() {return genericGetter<std::string>(chainType);}
    std::string getNumberingScheme() {return genericGetter<std::string>(numberingScheme);}
    matrix<double> getAminoAcidCharges() {return genericGetter<matrix<double>>(aminoAcidCharges);}
    std::vector<double> getTotalCharges() {return genericGetter<std::vector<double>>(total_charge);}

    // SETTERS

private:
    int numberOfChains;
    // optional attributes that are set from python API
    // or by specific constructors
    boost::optional<std::vector<std::string>> names;
    boost::optional<std::vector<std::string>> sequences;
    boost::optional<std::string> chainType;
    boost::optional<std::string> numberingScheme;
    boost::optional<matrix<double>> aminoAcidCharges;
    boost::optional<std::vector<double>> total_charge;

    std::vector<AntibodyChainCPP*> antibodyObjectPointers;
};

#endif //ABPYTOOLS_QT_CHAINCOLLECTIONCPP_H
