//
// Created by gil on 28/02/18.
//

#include "chainGroups.h"

void ChainGroups::addGroup(std::string name, std::string numberingScheme) {


    auto chainCollection = new ChainCollectionCPP();

    // makes sense to move, since this is the only copy we need
    chainCollection->setNumberingScheme(std::move(numberingScheme));

    chainCollectionGroups[name] = chainCollection;

    internalCounter++;

}


void ChainGroups::addChain(std::string chainGroupName_, std::string name_, std::string sequence_) {

    chainCollectionGroups[chainGroupName_]->append(name_, sequence_);

}


QStringList ChainGroups::getGroupNames() {

    QStringList keys;

    for (auto &pair: chainCollectionGroups) {
        keys.append(QString::fromStdString(pair.first));
    }

    return keys;
}

void ChainGroups::applyNumbering() {

    QTextStream out(stdout);

    out << "ERROR" << endl;

    for (auto &pair: chainCollectionGroups) {

        qDebug() << QString::fromStdString(pair.first) << " " << QString::fromStdString(pair.second->getNames()[0]);
        qDebug() << QString::fromStdString(pair.second->getSequences()[0]);

        try {
            pair.second->load();
        }
        catch (...) {
//            QTextStream out(stdout);
//
//            out << boost::current_exception_diagnostic_information() << endl;
//            qDebug() << QString::fromStdString(boost::current_exception_diagnostic_information());
        }

    }

}