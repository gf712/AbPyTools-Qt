//
// Created by gil on 22/02/18.
//

#ifndef ABPYTOOLS_QT_HYDROPHOBICITYPARSER_H
#define ABPYTOOLS_QT_HYDROPHOBICITYPARSER_H

#include "parser.h"
#include <iostream>
#include <unordered_map>
#include <vector>

class hydrophobicityParser: public Parser {

public:
    hydrophobicityParser(std::string filepath_): Parser(filepath_) {};
    ~hydrophobicityParser() = default;

    void parse();

    // GETTERS
    std::unordered_map<std::string, double> getAminoAcidHydrophobicityMap(int letter);

    bool ParserRules(std::string line) {}

private:
    std::string filepath;
    std::unordered_map<std::string, double> aminoAcidHydrophobicityMap;
    std::vector<double> hValues;

};

#endif //ABPYTOOLS_QT_HYDROPHOBICITYPARSER_H
