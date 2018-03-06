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

    // ADD DATA
    void addGroup(std::string name_, std::string numeringScheme_);
    void addChain(std::string groupName_, std::string name_, std::string sequence_);
    void addHydrophobicityValues(std::string groupName_, hydrophobicityParser *hParse);

    // PERFORM ANALYSIS
    void performPCA(std::string groupName, int nDimensions);
    void performPCA(QString groupName, int nDimensions);

    // SETTER
    void setNumberingScheme(std::string groupName_, std::string numberingScheme_);

    // GETTERS
    std::string getNumberingScheme(std::string groupName) {return chainCollectionGroups[groupName]->getNumberingScheme();}
    int getNumberOfSequences(std::string groupName) {return chainCollectionGroups[groupName]->getNumberOfChains();}

    QStringList getGroupNames();
    ChainCollectionCPP* getChainCollection(std::string groupName) { return chainCollectionGroups[groupName];}

    QString getInfo(std::string groupName);
    QString getInfo(QString groupName);

    QString getHydrophobicityParserName(std::string groupName_);
    QString getHydrophobicityParserName(QString groupName_);

    bool getPerformedPCA(std::string groupName) {return performedPCA[groupName];}
    bool getPerformedPCA(QString groupName) {return performedPCA[groupName.toStdString()];}

    bool getHasHDatabase(std::string groupName) {return hasHDatabase[groupName];}
    bool getHasHDatabase(QString groupName) {return hasHDatabase[groupName.toStdString()];}

    arma::mat getHydrophobicityValues(std::string chainGroupName_);

    QVector<double> getPrincipalComponent(QString chainGroupName_, int pc);

    void applyNumbering();

private:
    std::unordered_map<std::string, ChainCollectionCPP*> chainCollectionGroups;
    std::unordered_map<std::string, hydrophobicityParser*> chainCollectionHDatabase;
    std::unordered_map<std::string, bool> hasHDatabase;
    std::unordered_map<std::string, bool> performedPCA;
    int internalCounter;
};


#endif //ABPYTOOLS_QT_CHAINGROUPS_H
