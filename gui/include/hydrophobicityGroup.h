//
// Created by gil on 02/03/18.
//

#ifndef ABPYTOOLS_QT_HYDROPHOBICITYGROUP_H
#define ABPYTOOLS_QT_HYDROPHOBICITYGROUP_H

#include <unordered_map>
#include "hydrophobicityParser.h"

#include <QFileInfo>


class hydrophobicityGroups {

public:
    hydrophobicityGroups() {
        internalCounter = 0;
    };
    ~hydrophobicityGroups() = default;

    bool parseNewFile(std::string filename_);

    // GETTERS
    hydrophobicityParser* getHydrophobicityParser(std::string groupName) {return hValuesGroups[groupName]; }
    QStringList getDatasetNames();
//    QString getDatasetName()

private:

    std::unordered_map<std::string, hydrophobicityParser*> hValuesGroups;
    int internalCounter;
};


#endif //ABPYTOOLS_QT_HYDROPHOBICITYGROUP_H
