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
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/optional.hpp>

#include "pca.h"

using namespace boost::numeric::ublas;

class ChainCollectionCPP {
// This is a class containing CPP wrappers of the Chain python object
// The idea of this class is that once the chain objects are all loaded
// into the C++ wrapper it will be quicker to perform all the
// analysis with C++ rather than the already implemented python code

public:
    // CONSTRUCTORS
    ChainCollectionCPP(std::string NumberingScheme);
    ChainCollectionCPP(std::vector<AntibodyChainCPP> antibodyObjects);
    ChainCollectionCPP(char* path, char* numberingScheme);
    ~ChainCollectionCPP() = default;

    // METHODS
    void load(int setting=1, ChainCollectionCPP* newChainCollectionCPP=nullptr);
    void append(AntibodyChainCPP &AntibodyObject_);
    void append(AntibodyChainCPP *AntibodyObject_);
    void append(std::string name_, std::string sequence);

    void updateAntibodyObjectVector(AntibodyChainCPP &antibodyObject);
    void updateAntibodyObjectVector(AntibodyChainCPP *antibodyObject);

    void handleUnnumberedSequences(int setting, ChainCollectionCPP* newChainCollectionCPP);

    void removeChain(int index);
    void removeChain(std::string name);

    // GETTERS
    template <typename T>
    T genericGetter(boost::optional<T>);

    int getNumberOfChains() { return numberOfChains;}

    bool isLoaded() { return loaded;}
    bool isPartial() {return partial;}

    std::vector<std::string> getNames() {return names;}
    std::vector<std::string> getSequences() {return sequences;}
    std::string getChainType() {return chainType;}
    std::vector<AntibodyChainCPP*> getAntibodyObjectPointers() {return antibodyObjectPointers;}
    std::string getNumberingScheme() {return numberingScheme;}
    int getNTried() {return nTried;}
    AntibodyChainCPP* getAntibodyObject(int index) {return antibodyObjectPointers[index];}

    PCA* getPCAObject() { return !pcaObject ? throw "Error" : *pcaObject;}

//    matrix<double> getHydrophobicityValues(hydrophobicityParser &customHValues_);
    // ANALYSIS METHODS
    arma::mat getHydrophobicityValues(hydrophobicityParser &customHValues_, bool store=true);

    void performPCA(hydrophobicityParser &customHValues_, int nDimensions, bool store=false);
    void performPCA(int nDimensions);

    arma::vec getPrincipalComponent(int pc);

    matrix<double> getAminoAcidCharges() {return genericGetter<matrix<double>>(aminoAcidCharges);}
    std::vector<double> getTotalCharges() {return genericGetter<std::vector<double>>(total_charge);}

    // SETTERS
    void setNumberingScheme(std::string numberingScheme_) { numberingScheme = numberingScheme_;}
    void setChainType(std::string chainType_) {chainType = chainType_;}
    void setLoaded(bool loaded_) {loaded = loaded_;}
    void setPartial(bool partial_) {partial = partial_;}

private:
    bool partial;
    int numberOfChains;
    bool loaded;
    int nLoaded;
    int nFailed;
    int nTried;
    // optional attributes that are set from python API
    // or by specific constructors
    std::vector<std::string> names;
    std::vector<std::string> sequences;

    std::string numberingScheme;
    std::string chainType;

    boost::optional<arma::mat> hydrophobicityMatrix;
    boost::optional<matrix<double>> aminoAcidCharges;
    boost::optional<std::vector<double>> total_charge;

    std::vector<AntibodyChainCPP*> antibodyObjectPointers;

    boost::optional<PCA*> pcaObject;

    std::unordered_map<std::string, bool> loadedMap;
};

#endif //ABPYTOOLS_QT_CHAINCOLLECTIONCPP_H
