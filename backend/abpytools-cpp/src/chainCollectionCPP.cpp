//
// Created by gil on 21/02/18.
//

#include "../include/chainCollectionCPP.h"
#include <string>

void checkCollection(ChainCollectionCPP &chainCollectionObject, int setting) {

    bool partial = false;

    std::string chainType_ = chainCollectionObject.getAntibodyObjectPointers()[0]->getChain();
    std::string numberingScheme_ = chainCollectionObject.getAntibodyObjectPointers()[0]->getNumberingScheme();

    for (auto const &antibodyObject: chainCollectionObject.getAntibodyObjectPointers()) {

        if (antibodyObject->getNumberingScheme() != numberingScheme_) {
            throw "Not all the chains were numbered with the same scheme!";
        }

        // check if they are all of the same chain type
        if (antibodyObject->getChain() != chainType_) {
            if (setting > 0) throw "Not all chains are of the same type!"; // should be all the same
            else if (setting == 0) partial=true;
        }

        if (!antibodyObject->isAligned()) {
            // this means that there is a sequence that was not numbered properly
            if (setting == 1) {
                // this is a sanity check, with setting=1 we should never have
                // a sequence in a ChainCollectionCPP object that has failed to be
                // numbered as these will be deleted immediately
                throw "Antibody was not aligned! (YOU SHOULD NEVER SEE THIS ERROR)";
            }
            // if setting=0 then loaded will be false
            partial = true;
        }
    }

    // no errors
    chainCollectionObject.setPartial(partial);
    chainCollectionObject.setChainType(chainType_);
}


ChainCollectionCPP::ChainCollectionCPP(std::string numbering_scheme) {

    // constructor without any objects
    numberOfChains = 0;
    loaded = false;
    nLoaded = 0;
    nFailed = 0;
    nTried = 0;
    numberingScheme = numbering_scheme;
    partial = false;
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
    partial = false;

}

ChainCollectionCPP::ChainCollectionCPP(char *path, char *numberingScheme) {
    // method to read in fasta files and .json files
    throw "I DO NOT EXIST YET!";
}

template <typename T>
T ChainCollectionCPP::genericGetter(boost::optional<T> optionalParam_) {
    // handles all getter that are wrapped in boost::optional
    if (!optionalParam_)
        throw nullptr;
    else
        return *optionalParam_;
}

void ChainCollectionCPP::load(int setting, ChainCollectionCPP* newChainCollectionCPP) {

    // setting controls the behaviour when a sequence cannot be numbered:
    // 0 - creates a new ChainCollectionCPP with all numbered sequences
    // 1 - delete the entries that were not numbered

    std::cout << "nTried: " << nTried
              << "nFailed: " << nFailed
              << "nLoaded: " << nLoaded
              << std::endl;

    // reset number of tries
    nTried = 0;

    // TODO: add openmp support to project and use it here to submit several requests at a time
    for (auto const &antibodyObject: antibodyObjectPointers) {

        std::cout << "iterating over " << antibodyObject->getName() << std::endl;

        if (!antibodyObject->isAligned() and antibodyObject->getStatus() != "Unnumbered") {

            try {
                antibodyObject->load();
//                if (!antibodyObject->isAligned())
//                    nFailed++;
//                else
                nLoaded++;
            }
            catch (NumberingException) {
//                throw "Could not number sequence";
                nFailed++;
            }
            catch (ConnectionException)
            {
//                throw "Could not submit sever request";
                nFailed++;
            }
            catch (...){
                throw "Unexpected error!";
            }

            nTried++;
        }

        else if (antibodyObject->getStatus() == "Unnumbered") nFailed++;

        else {
            std::cout << "Sequence already aligned" << std::endl;
        }
    }

    loaded = true;

    handleUnnumberedSequences(setting, newChainCollectionCPP);

    // run final checks
    checkCollection(*this, setting);

    if (setting == 0) {
        newChainCollectionCPP->setLoaded(true);
        checkCollection(*newChainCollectionCPP, setting); // checks new ChainCollectionCPP
    }
}


void ChainCollectionCPP::handleUnnumberedSequences(int setting, ChainCollectionCPP* newChainCollectionCPP) {

    if (setting == 0) {

        if (newChainCollectionCPP == nullptr) {
            throw "Expected a ChainCollectionCPP object to append numbered chains!";
        }

        for (auto const &antibodyObject: antibodyObjectPointers) {

            if (antibodyObject->isAligned()) {
                // aligned sequences are copied to a new ChainCollectionCPP object
                newChainCollectionCPP->append(antibodyObject);
            }
        }
    }

    else if (setting == 1) {

        // iterate over each object and check if it has been numbered
        int i = 0;
        for (auto const &antibodyObject: antibodyObjectPointers) {

            if (!antibodyObject->isAligned()) {
                // if the sequence has not been aligned remove all
                // entries related to it
                removeChain(i);
            }
            else i++;
        }
    }
}


void ChainCollectionCPP::removeChain(int index) {
    numberOfChains--;
    names.erase(names.begin()+index);
    sequences.erase(sequences.begin()+index);
    antibodyObjectPointers.erase(antibodyObjectPointers.begin()+index);
}

void ChainCollectionCPP::append(AntibodyChainCPP &antibodyObject_) {
    // append by reference
    // function to append more antibody objects
    std::cout << "Appending: " << antibodyObject_.getName() << std::endl;

    updateAntibodyObjectVector(antibodyObject_);

    std::cout << "Number of chains: " << antibodyObjectPointers.size() << std::endl;

}

void ChainCollectionCPP::append(AntibodyChainCPP *antibodyObject_) {
    // append pointer
    // function to append more antibody objects
    std::cout << "Appending: " << antibodyObject_->getName() << std::endl;

    updateAntibodyObjectVector(antibodyObject_);

    std::cout << "Number of chains: " << antibodyObjectPointers.size() << std::endl;


}

void ChainCollectionCPP::append(std::string name_, std::string sequence_) {

    std::cout << "Appending: " << name_ << std::endl;

    // function to append more antibody objects, using name and sequence
    auto antibodyObject = new AntibodyChainCPP(sequence_, name_, numberingScheme);

    updateAntibodyObjectVector(*antibodyObject);

    std::cout << "Number of chains: " << antibodyObjectPointers.size() << std::endl;

}

void ChainCollectionCPP::updateAntibodyObjectVector(AntibodyChainCPP &antibodyObject) {

    std::cout << "Appending by reference" << "\n";

    names.emplace_back(antibodyObject.getName());
    sequences.emplace_back(antibodyObject.getSequence());
    antibodyObjectPointers.emplace_back(&antibodyObject);
    numberOfChains++;

    std::cout << "Appended by reference" << "\n";

}

void ChainCollectionCPP::updateAntibodyObjectVector(AntibodyChainCPP *antibodyObject) {

    std::cout << "Appending pointer" << "\n";

    names.emplace_back(antibodyObject->getName());
    sequences.emplace_back(antibodyObject->getSequence());
    antibodyObjectPointers.emplace_back(antibodyObject);
    numberOfChains++;

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

    std::cout << "H matrix cols: " << hMatrix.n_cols << std::endl;
    std::cout << "H matrix rows: " << hMatrix.n_rows << std::endl;

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

    std::cout << "H matrix cols: " << (*hydrophobicityMatrix).n_cols << std::endl;
    std::cout << "H matrix rows: " << (*hydrophobicityMatrix).n_rows << std::endl;

    (*pcaObject)->fit(*hydrophobicityMatrix);

}


arma::vec ChainCollectionCPP::getPrincipalComponent(int pc) {

    // get PCs
    if (!pcaObject) {
        // if pcaObject method fit hasn't been called throw error
        throw "pcaObject fit method has to be called first";
    }

    return (*pcaObject)->getTransformedData().submat(arma::span::all, arma::span(pc));

}
