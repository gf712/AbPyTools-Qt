//
// Created by gil on 28/02/18.
//

#include "chainGroups.h"

void ChainGroups::addGroup(std::string name, std::string numberingScheme) {


    auto chainCollection = new ChainCollectionCPP();

    chainCollection->setNumberingScheme(numberingScheme);

    chainCollectionGroups[name] = chainCollection;

    internalCounter++;

}
