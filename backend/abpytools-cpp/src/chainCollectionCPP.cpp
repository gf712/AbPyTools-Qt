//
// Created by gil on 21/02/18.
//

#include "../include/chainCollectionCPP.h"
#include <string>

ChainCollectionCPP::ChainCollectionCPP() {

    // constructor without any objects
    numberOfChains = 0;
    loaded = false;
    nLoaded = 0;
    nFailed = 0;
    nTried = 0;

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

    nLoaded = 0;
    nFailed = 0;
    nTried = 0;

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

    std::cout << "nTried: " << nTried
              << "nFailed: " << nFailed
              << "nLoaded: " << nLoaded
              << std::endl;

    // TODO: add openmp support to project and use it here
    for (auto const &antibodyObject: antibodyObjectPointers) {

        std::cout << "iterating over " << antibodyObject->getName() << std::endl;

        if (!antibodyObject->isAligned()) {

            try {
                antibodyObject->load();
                if (!antibodyObject->isAligned())
                    nFailed++;
                else
                    nLoaded++;
            }
            catch (...) {
                throw "Could not load sequence";
                nFailed++;
            }

            nTried++;
        }
        else {
            std::cout << "Sequence already aligned" << std::endl;
        }
    }

    std::string chainType_ = antibodyObjectPointers[0]->getChain();
    std::string numberingScheme_ = antibodyObjectPointers[0]->getNumberingScheme();

    // check if they are all of the same chain type
    for (auto const &antibodyObject: antibodyObjectPointers) {

        if (antibodyObject->getChain() != chainType_) {
            // write exception
            throw "Not all chains are of the same type!";
        }

        if (antibodyObject->getNumberingScheme() != numberingScheme_) {
            throw "Not all the chains were numerbered with the same scheme!";
        }
        if (!antibodyObject->isAligned())
            throw "Antibody was not aligned!";
    }

    // no errors
    chainType = chainType_;
    numberingScheme = numberingScheme_;
    loaded = true;

}

void ChainCollectionCPP::append(AntibodyChainCPP &antibodyObject_) {

    // function to append more antibody objects
    updateAntibodyObjectVector(antibodyObject_);

}

void ChainCollectionCPP::append(std::string name_, std::string sequence_) {

    // function to append more antibody objects, using name and sequence
    auto antibodyObject = new AntibodyChainCPP(sequence_, name_, numberingScheme);

    updateAntibodyObjectVector(*antibodyObject);

}

void ChainCollectionCPP::updateAntibodyObjectVector(AntibodyChainCPP &antibodyObject) {

    std::cout << "Appending pointer" << "\n";

    names.emplace_back(antibodyObject.getName());
    sequences.emplace_back(antibodyObject.getSequence());
    numberOfChains++;
    antibodyObjectPointers.emplace_back(&antibodyObject);

    std::cout << "Appended pointer" << "\n";

}


arma::mat ChainCollectionCPP::getHydrophobicityValues(hydrophobicityParser &customHValues_, bool store) {

    arma::mat hydrophobicityMatrix_(0,0);

    if (chainType == "heavy")
        hydrophobicityMatrix_.resize(numberOfChains, 158);
    else if (chainType == "light")
        hydrophobicityMatrix_.resize(numberOfChains, 120);
    else
        throw ChainSequenceNotNumberedException(chainType);

    for (int i = 0; i < numberOfChains; ++i) {

        auto chainHVector = antibodyObjectPointers[i]->getHydrophobicityMatrix(customHValues_);

//        std::cout << "ROWVEC SIZE: " << arma::conv_to<arma::rowvec>::from(chainHVector).size() << std::endl;

        hydrophobicityMatrix_.row(i) = arma::conv_to<arma::rowvec>::from(chainHVector);
    }

    // store data in optional class member hydrophobicityMatrix
    if (store)
        hydrophobicityMatrix = hydrophobicityMatrix_;

    return hydrophobicityMatrix_;
}

void ChainCollectionCPP::performPCA(hydrophobicityParser &customHValues_, int nDimensions, bool store) {

    // performs PCA with given hydrophobicityParser

    // by default does not keep matrix
    auto hMatrix = getHydrophobicityValues(customHValues_, store);

    if (store) hydrophobicityMatrix = hMatrix;

    if (!pcaObject) {
        pcaObject = new PCA(nDimensions);
    }
    else {
        (*pcaObject)->setNDimensions(nDimensions);
    }

    (*pcaObject)->fit(hMatrix);

}

void ChainCollectionCPP::performPCA(int nDimensions) {

    // performs PCA with cached matrix (if none available throws exception)

    if (!hydrophobicityMatrix) {
        throw "No hydrophobicity matrix cached";
    }

    if (!pcaObject) {
        pcaObject = new PCA(nDimensions);
    }
    else {
        (*pcaObject)->setNDimensions(nDimensions);
    }

    (*pcaObject)->fit(*hydrophobicityMatrix);

}


arma::vec ChainCollectionCPP::getPrincipalComponent(int pc) {

    // get PCs
    if (!pcaObject) {
        // if pcaObject method fit hasn't been called throw error
        throw "pcaObject fit method has to be called first";
    }

    std::cout << "EigVec cols: " << (*pcaObject)->getEigenvectors().n_cols << "\n";
    std::cout << "EigVec rows: " << (*pcaObject)->getEigenvectors().n_rows << "\n";

    return (*pcaObject)->getEigenvectors().submat(arma::span::all, arma::span(pc));

}
