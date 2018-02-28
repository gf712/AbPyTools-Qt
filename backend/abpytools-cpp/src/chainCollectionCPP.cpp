//
// Created by gil on 21/02/18.
//

#include "../include/chainCollectionCPP.h"
#include <string>

ChainCollectionCPP::ChainCollectionCPP() {

    // constructor without any objects
    numberOfChains = 0;

}

ChainCollectionCPP::ChainCollectionCPP(std::vector <AntibodyChainCPP> antibodyObjects_) {

    // constructor with a vector with AntibodyChainCPP objects

    // check if all chains are either heavy or light and assert
    // they all conform to the same numbering scheme
    for (auto &antibodyObject: antibodyObjects_) {

        if (antibodyObject.getChain() != antibodyObjects_[0].getChain()) {
            // write exception
            throw 1;
        }

        if (antibodyObject.getNumberingScheme() != antibodyObjects_[0].getNumberingScheme()) {
            throw 1;
        }

    }

    numberOfChains = 0;
    chainType = std::string(antibodyObjects_[0].getChain());
    numberingScheme = std::string(antibodyObjects_[0].getNumberingScheme());

    // all good, so now we can copy all into C++ objects
    for (auto &antibodyObject: antibodyObjects_) {

        updateAntibodyObjectVector(antibodyObject);

    }

}

ChainCollectionCPP::ChainCollectionCPP(char *path, char *numberingScheme) {
    // method to read in fasta files and .json files
}

template <typename T>
T ChainCollectionCPP::genericGetter(boost::optional<T> optionalParam_) {
    // handles all getter that are wrapped in boost::optional
    if (!optionalParam_)
        throw nullptr;
    else
        return *optionalParam_;
}

void ChainCollectionCPP::load() {

    // TODO: add openmp support to project and use it here
    for (auto &antibodyObject: antibodyObjectPointers) {
        antibodyObject->load();
    }
}

void ChainCollectionCPP::append(AntibodyChainCPP &antibodyObject_) {

    // function to append more antibody objects
    updateAntibodyObjectVector(antibodyObject_);

}

void ChainCollectionCPP::updateAntibodyObjectVector(AntibodyChainCPP antibodyObject) {

    std::cout << "Appending pointer" << "\n";

    names.emplace_back(antibodyObject.getName());
    sequences.emplace_back(antibodyObject.getSequence());
    numberOfChains++;
    antibodyObjectPointers.emplace_back(&antibodyObject);

    std::cout << "Appended pointer" << "\n";

}