//
// Created by gil on 28/02/18.
//

#include "chainGroups.h"

void ChainGroups::addGroup(std::string name, std::string numberingScheme) {


    auto chainCollection = new ChainCollectionCPP();

    // makes sense to move, since this is the only copy we need
    chainCollection->setNumberingScheme(std::move(numberingScheme));

    chainCollectionGroups[name] = chainCollection;

    performedPCA[name] = false;
    hasHDatabase[name] = false;

    internalCounter++;

}


void ChainGroups::addChain(std::string chainGroupName_, std::string name_, std::string sequence_) {

    chainCollectionGroups[chainGroupName_]->append(name_, sequence_);

}


void ChainGroups::addHydrophobicityValues(std::string chainGroupName_, hydrophobicityParser *hParser) {

    chainCollectionHDatabase[chainGroupName_] = hParser;
    hasHDatabase[chainGroupName_] = true;

}


arma::mat ChainGroups::getHydrophobicityValues(std::string chainGroupName_) {

    return chainCollectionGroups[chainGroupName_]->getHydrophobicityValues(*chainCollectionHDatabase[chainGroupName_]);

}


QStringList ChainGroups::getGroupNames() {

    QStringList keys;

    for (auto &pair: chainCollectionGroups) {
        keys.append(QString::fromStdString(pair.first));
    }

    return keys;
}

QString ChainGroups::getInfo(std::string groupName) {

    QString text = "Group name: %1\n"
            "   - number of sequences: %2\n"
            "   - numbering scheme: %3\n"
            "   - loaded: %4\n"
            "   - hydrophobicity values: %5\n";

    QString boolText = chainCollectionGroups[groupName]->isLoaded() ? "true" : "false";

    text = text.arg(QString::fromStdString(groupName),
                    QString::number(chainCollectionGroups[groupName]->getNumberOfChains()),
                    QString::fromStdString(chainCollectionGroups[groupName]->getNumberingScheme()),
                    boolText,
                    QString(getHydrophobicityParserName(groupName)),
                    QString::fromStdString(chainCollectionGroups[groupName]->getChainType()));
    return text;

}

QString ChainGroups::getInfo(QString groupName) {

    QString text = "Group name: %1\n"
            "   - number of sequences: %2\n"
            "   - numbering scheme: %3\n"
            "   - loaded: %4\n"
            "   - hydrophobicity values: %5\n"
            "   - chain type: %6\n";

    QString boolText = chainCollectionGroups[groupName.toStdString()]->isLoaded() ? "true" : "false";

    text = text.arg(groupName,
                    QString::number(chainCollectionGroups[groupName.toStdString()]->getNumberOfChains()),
                    QString::fromStdString(chainCollectionGroups[groupName.toStdString()]->getNumberingScheme()),
                    boolText,
                    QString(getHydrophobicityParserName(groupName)),
                    QString::fromStdString(chainCollectionGroups[groupName.toStdString()]->getChainType()));

    return text;

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


void ChainGroups::setNumberingScheme(std::string groupName_, std::string numberingScheme_) {

    chainCollectionGroups[groupName_]->setNumberingScheme(numberingScheme_);

}


QString ChainGroups::getHydrophobicityParserName(std::string groupName_) {

    if (chainCollectionHDatabase.find(groupName_) != chainCollectionHDatabase.end()) {
        return QString::fromStdString(chainCollectionHDatabase[groupName_]->getBasename());
    }
    else {
        return QString("None");
    }
}


QString ChainGroups::getHydrophobicityParserName(QString groupName_) {

    if (chainCollectionHDatabase.find(groupName_.toStdString()) != chainCollectionHDatabase.end()) {
        return QString::fromStdString(chainCollectionHDatabase[groupName_.toStdString()]->getBasename());
    }
    else {
        return QString("None");
    }
}


void ChainGroups::performPCA(std::string groupName, int nDimensions) {

    if (!hasHDatabase[groupName]) {
        throw "Error";
    }

    // perform PCA with given hydrophobicity dataset
    chainCollectionGroups[groupName]->performPCA(*chainCollectionHDatabase[groupName], nDimensions);
    performedPCA[groupName] = true;
}

void ChainGroups::performPCA(QString groupName, int nDimensions) {
    // perform PCA with given hydrophobicity dataset

    if (!hasHDatabase[groupName.toStdString()]) {
        throw "Error";
    }

    chainCollectionGroups[groupName.toStdString()]->performPCA(*chainCollectionHDatabase[groupName.toStdString()], nDimensions);
    performedPCA[groupName.toStdString()] = true;
}

QVector<double> ChainGroups::getPrincipalComponent(QString chainGroupName_, int pc) {

    QVector<double> result;

    // get PC from chain collection
    for (auto const &value: chainCollectionGroups[chainGroupName_.toStdString()]->getPrincipalComponent(pc)) {

        result.append(value);

    }

    return result;
}