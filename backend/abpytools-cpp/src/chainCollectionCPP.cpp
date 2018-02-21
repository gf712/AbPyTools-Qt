//
// Created by gil on 21/02/18.
//

#include "chainCollectionCPP.h"

ChainCollectionCPP::ChainCollectionCPP(std::vector <AntibodyChainCPP> antibodyObjects) {

    // constructor with a vector with AntibodyChainCPP objects

    // check if all chains are either heavy or light
    for (auto antibodyObject: antibodyObjects) {
        auto* chain_i = antibodyObject.getChain();

        if (chain_i != antibodyObjects[0].getChain()) {
            // write exception
            throw 1;
        }
    }

    // all good, so now we can copy all into C++ objects
    for (auto antibodyObject: antibodyObjects) {

    }

}

ChainCollectionCPP::ChainCollectionCPP(char *path, char *numberingScheme) {

}
