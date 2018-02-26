//
// Created by gil on 21/02/18.
//

#include "../include/chainCollectionCPP.h"
#include <string>

ChainCollectionCPP::ChainCollectionCPP(std::vector <AntibodyChainCPP> antibodyObjects) {

    // constructor with a vector with AntibodyChainCPP objects

    // check if all chains are either heavy or light and assert
    // they all conform to the same numbering scheme
    for (auto antibodyObject: antibodyObjects) {

        if (antibodyObject.getChain() != antibodyObjects[0].getChain()) {
            // write exception
            throw 1;
        }

        if (antibodyObject.getNumberingScheme() != antibodyObjects[0].getNumberingScheme()) {
            throw 1;
        }

    }

    numberOfChains = 0;
    chainType = std::string(antibodyObjects[0].getChain());
    numberingScheme = std::string(antibodyObjects[0].getNumberingScheme());

    // all good, so now we can copy all into C++ objects
    for (auto antibodyObject: antibodyObjects) {
        names.emplace_back(antibodyObject.getName());
        sequences.emplace_back(antibodyObject.getSequence());
        numberOfChains++;
    }



}

ChainCollectionCPP::ChainCollectionCPP(char *path, char *numberingScheme) {

}
