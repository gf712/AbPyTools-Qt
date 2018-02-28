//
// Created by gil on 28/02/18.
//

#ifndef ABPYTOOLS_QT_CHAINGROUPS_H
#define ABPYTOOLS_QT_CHAINGROUPS_H

#include <unordered_map>
#include "chainCollectionCPP.h"

class ChainGroups {

public:
    ChainGroups() {
        internalCounter = 0;
    };
    ~ChainGroups();

    void addGroup(ChainCollectionCPP *chainCollectionCPP_);

private:
    std::unordered_map<std::string, ChainCollectionCPP*> chainCollectionGroups;
    int internalCounter;
};



#endif //ABPYTOOLS_QT_CHAINGROUPS_H
