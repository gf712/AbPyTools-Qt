//
// Created by gil on 28/02/18.
//

#include <QtCore/QStringList>
#include "chainGroups.h"

#include <utility>

void ChainGroups::addGroup(std::string name, std::string numberingScheme) {


    auto chainCollection = new ChainCollectionCPP();

    // makes sense to move, since this is the only copy we need
    chainCollection->setNumberingScheme(std::move(numberingScheme));

    chainCollectionGroups[name] = chainCollection;

    internalCounter++;

}


QStringList ChainGroups::getGroupNames() {

    QStringList keys;

    for (auto &pair: chainCollectionGroups) {
        keys.append(QString::fromStdString(pair.first));
    }

    return keys;
}
