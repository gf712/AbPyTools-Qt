//
// Created by gil on 28/02/18.
//

#ifndef ABPYTOOLS_QT_CHAINGROUPS_H
#define ABPYTOOLS_QT_CHAINGROUPS_H

#include <unordered_map>
#include "chainCollectionCPP.h"

#include "hydrophobicityParser.h"

#include <utility>
#include <QDebug>


class ChainGroups {

public:
    ChainGroups() {
        internalCounter = 0;
    };
    ~ChainGroups() = default;

    void addGroup(std::string name_, std::string numeringScheme_);
    void addChain(std::string groupName_, std::string name_, std::string sequence_);
    void addHydrophobicityValues(std::string groupName_, hydrophobicityParser *hParse);

    // SETTER
    void setNumberingScheme(std::string groupName_, std::string numberingScheme_);

    // GETTERS
    std::string getNumberingScheme(std::string groupName) {return chainCollectionGroups[groupName]->getNumberingScheme();}
    int getNumberOfSequences(std::string groupName) {return chainCollectionGroups[groupName]->getNumberOfChains();}
    QStringList getGroupNames();
    ChainCollectionCPP* getChainCollection(std::string groupName) { return chainCollectionGroups[groupName];}
    QString getInfo(std::string groupName);
    QString getInfo(QString groupName);

    matrix<double> getHydrophobicityValues(std::string chainGroupName_);

    void applyNumbering();

private:
    std::unordered_map<std::string, ChainCollectionCPP*> chainCollectionGroups;
    std::unordered_map<std::string, hydrophobicityParser*> chainCollectionHDatabase;
    int internalCounter;
};


#endif //ABPYTOOLS_QT_CHAINGROUPS_H
