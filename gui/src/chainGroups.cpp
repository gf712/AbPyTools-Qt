//
// Created by gil on 28/02/18.
//

#include "chainGroups.h"

void ChainGroups::addGroup(ChainCollectionCPP *chainCollectionCPP_) {

    auto name = "Group_%i";

    printf(name, internalCounter);

    chainCollectionGroups[std::string(name)] = chainCollectionCPP_;

    internalCounter++;

}
