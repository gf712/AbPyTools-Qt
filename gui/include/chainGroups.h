//
// Created by gil on 28/02/18.
//

#ifndef ABPYTOOLS_QT_CHAINGROUPS_H
#define ABPYTOOLS_QT_CHAINGROUPS_H

#include <unordered_map>
#include "chainCollectionCPP.h"
#include <utility>
#include <QtCore/QStringList>
#include <QDebug>

class ChainGroups {

public:
    ChainGroups() {
        internalCounter = 0;
    };
    ~ChainGroups();

    void addGroup(std::string name_, std::string numeringScheme_);
    void addChain(std::string groupName_, std::string name_, std::string sequence_);

    // GETTERS
    std::string getNumberingScheme(std::string groupName) {return chainCollectionGroups[groupName]->getNumberingScheme();}
    int getNumberOfSequences(std::string groupName) {return chainCollectionGroups[groupName]->getNumberOfChains();}
    QStringList getGroupNames();
    ChainCollectionCPP* getChainCollection(std::string groupName) { return chainCollectionGroups[groupName];}

    void applyNumbering();

private:
    std::unordered_map<std::string, ChainCollectionCPP*> chainCollectionGroups;
    int internalCounter;
};


#endif //ABPYTOOLS_QT_CHAINGROUPS_H
