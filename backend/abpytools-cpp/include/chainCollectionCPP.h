//
// Created by gil on 21/02/18.
//

#ifndef ABPYTOOLS_QT_CHAINCOLLECTIONCPP_H
#define ABPYTOOLS_QT_CHAINCOLLECTIONCPP_H

#include <vector>
#include <string>
#include "chain.h"
#include <boost/numeric/ublas/matrix.hpp>

using namespace boost::numeric::ublas;

class ChainCollectionCPP {
// This is a class containing CPP wrappers of the Chain python object
// The idea of this class is that once the chain objects are all loaded
// into the C++ wrapper it will be quicker to perform all the
// analysis with C++ rather than the already implemented python code

public:
    ChainCollectionCPP(std::vector<AntibodyChainCPP> antibodyObjects);
    ChainCollectionCPP(char* path, char* numberingScheme);
    ~ChainCollectionCPP() = default;

private:
    std::vector<std::string> names;
    std::vector<std::string> sequences;
    int numberOfChains;
    std::string chainType;
    std::string numberingScheme;
    matrix<double> aminoAcidCharges;
    std::vector<double> total_charge;
};

#endif //ABPYTOOLS_QT_CHAINCOLLECTIONCPP_H
