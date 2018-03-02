//
// Created by gil on 02/03/18.
//

#include "../include/hydrophobicityGroup.h"

bool hydrophobicityGroups::parseNewFile(std::string filename_) {

    try {

        auto hParser = new hydrophobicityParser(filename_);

        hParser->parse();

        QFileInfo fi(QString::fromStdString(filename_));

        hValuesGroups[fi.baseName().toStdString()] = hParser;

        internalCounter++;

        return true;
    }
    catch (...) {

        return false;

    }
}

QStringList hydrophobicityGroups::getDatasetNames() {

    QStringList keys;

    for (auto &pair: hValuesGroups) {
        keys.append(QString::fromStdString(pair.first));
    }

    return keys;
}