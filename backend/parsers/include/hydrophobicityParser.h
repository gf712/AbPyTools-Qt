//
// Created by gil on 22/02/18.
//

#ifndef ABPYTOOLS_QT_HYDROPHOBICITYPARSER_H
#define ABPYTOOLS_QT_HYDROPHOBICITYPARSER_H

#include <iostream>
#include <unordered_map>
#include <vector>

class hydrophobicityParser {

public:
    hydrophobicityParser(std::string &filepath_);
    ~hydrophobicityParser() = default;

    void parse();

    // GETTERS
    std::unordered_map<std::string, double> getAminoAcidHydrophobicityMap() {return aminoAcidHydrophobicityMap;}
    std::string getFilepath() { return  filepath;}

private:
    std::string filepath;
    std::unordered_map<std::string, double> aminoAcidHydrophobicityMap;
    std::vector<double> hValues;

};

#endif //ABPYTOOLS_QT_HYDROPHOBICITYPARSER_H
