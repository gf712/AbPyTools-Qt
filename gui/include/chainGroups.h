//
// Created by gil on 28/02/18.
//

#ifndef ABPYTOOLS_QT_CHAINGROUPS_H
#define ABPYTOOLS_QT_CHAINGROUPS_H

#include <unordered_map>
#include <utility>
#include <boost/range/combine.hpp>
#include <boost/foreach.hpp>
#include "chainCollectionCPP.h"
#include "connection_check.h"

#include "hydrophobicityParser.h"
#include "fastaParser.h"

#include <QDebug>

class ChainGroups {

public:
    ChainGroups() {
        internalCounter = 0;
    };
    ~ChainGroups() = default;

    // ADD DATA
    void addGroup(std::string name_, std::string numeringScheme_);
    void addChain(std::string groupName_, std::string name_, std::string sequence_);
    void addHydrophobicityValues(std::string groupName_, hydrophobicityParser *hParse);

    // REMOVE DATA
    void removeGroup(std::string groupName_);

    // PERFORM ANALYSIS
    void performPCA(std::string groupName, int nDimensions);
    void performPCA(QString groupName, int nDimensions);

    // SETTER
    void setNumberingScheme(std::string groupName_, std::string numberingScheme_);

    // GETTERS
    std::string getNumberingScheme(std::string groupName) {
        if (groupExists(groupName)) return chainCollectionGroups[groupName]->getNumberingScheme();
        else throw "Group does not exist!";
    }

    int getNumberOfSequences(std::string groupName) {
        if (groupExists(groupName)) return chainCollectionGroups[groupName]->getNumberOfChains();
        else throw "Group does not exist!";
    }

    QStringList getGroupNames();
    ChainCollectionCPP* getChainCollection(std::string groupName) { return chainCollectionGroups[groupName];}

    QString getHydrophobicityParserName(std::string groupName_);
    QString getHydrophobicityParserName(QString groupName_);

    bool getPerformedPCA(std::string groupName) {return performedPCA[groupName];}
    bool getPerformedPCA(QString groupName) {return performedPCA[groupName.toStdString()];}

    bool getHasHDatabase(std::string groupName) {return hasHDatabase[groupName];}
    bool getHasHDatabase(QString groupName) {return hasHDatabase[groupName.toStdString()];}

    arma::mat getHydrophobicityValues(std::string chainGroupName_);

    QVector<double> getPrincipalComponent(QString chainGroupName_, int pc);

    void applyNumbering(int setting);
    void loadFASTA(std::string chainGroupName_, std::string filename_);

    double fastaParsingProgress(std::string groupName_);
    double numberingProgress();

    // MAINTENANCE
    QString getInfo(std::string groupName);
    QString getInfo(QString groupName);
    bool groupExists(QString groupName_) {chainCollectionGroups.find(groupName_.toStdString()) != chainCollectionGroups.end();}
    bool groupExists(std::string groupName_) {chainCollectionGroups.find(groupName_) != chainCollectionGroups.end();}
    bool isAbnumConnected() {
        std::cout << "[ChainGroups] Is abnum connected: " << abnumConnection();
        return abnumConnection();
    }


private:
    std::unordered_map<std::string, double> groupFASTALoadingProgressRecord;
    std::unordered_map<std::string, ChainCollectionCPP*> chainCollectionGroups;
    std::unordered_map<std::string, hydrophobicityParser*> chainCollectionHDatabase;
    std::unordered_map<std::string, bool> hasHDatabase;
    std::unordered_map<std::string, bool> performedPCA;
    int internalCounter;
};


#endif //ABPYTOOLS_QT_CHAINGROUPS_H
