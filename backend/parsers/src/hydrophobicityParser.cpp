//
// Created by gil on 22/02/18.
//

#include "hydrophobicityParser.h"
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include "exception.h"

std::vector<std::string> aaList{"ALA", "ARG", "ASN", "ASP", "CYS", "GLN", "GLU",
                                "GLY", "HIS", "ILE", "LEU", "LYS", "MET", "PHE",
                                "PRO", "SER", "THR", "TRP", "TYR", "VAL"};

std::unordered_map<std::string, std::string> aaOnetoThreeAA{{"ALA", "A"}, {"ARG", "R"}, {"ASN", "N"}, {"ASP", "D"},
                                                            {"CYS", "C"}, {"GLN", "Q"}, {"GLU", "E"}, {"GLY", "G"},
                                                            {"HIS", "H"}, {"ILE", "I"}, {"LEU", "L"}, {"LYS", "K"},
                                                            {"MET", "M"}, {"PHE", "F"}, {"PRO", "P"}, {"SER", "S"},
                                                            {"THR", "T"}, {"TRP", "W"}, {"TYR", "Y"}, {"VAL", "V"}};

template<class T>
std::unordered_map<std::string, T> convertOneToThreeMap(std::unordered_map<std::string, T> threeLetterMap) {

    std::unordered_map<std::string, T> newMap;

    for (const auto& pair: threeLetterMap) {

        newMap[aaOnetoThreeAA[pair.first]] = pair.second;

//        std::cout << pair.first << pair.second;

    }

    return newMap;
};

hydrophobicityParser::hydrophobicityParser(std::string &filepath_) {

    if (!boost::filesystem::exists(filepath_)) {
        // write exception
        throw FileDoesNotExistException("Unknown filepath: " + boost::filesystem::canonical(filepath_).string());
    }

    // get absolute file path just to be on the safe side..
    filepath = boost::filesystem::canonical(filepath_).string();
}

void hydrophobicityParser::parse() {

    boost::filesystem::ifstream file(filepath);

    for (std::string line; std::getline(file, line); )
    {

        // process "line"
        // if line startswith "!" it's just a comment
        std::string commentChar = "!";

        if (line.compare(0, 1, commentChar) != 0) {

            // should contain relevant info
            std::vector<std::string> elements;
            boost::split(elements, line, boost::is_any_of("\t "), boost::token_compress_on);

            if (std::find(aaList.begin(), aaList.end(), elements[0]) == std::end(aaList)) {
                // first element of line not in aaList -> throw error
                // or should this be more tolerant to mistakes?
                throw 1;
            }

            double numericHValue;

            // all good, now convert second element to double
            try {
                numericHValue = boost::lexical_cast<double>(elements[1]);
            }
            catch (boost::bad_lexical_cast &msg) {
            // error whilst trying to extract double from string
                throw nullptr;
            }

            aminoAcidHydrophobicityMap[elements[0]] = numericHValue;

        }
    }

    if (aminoAcidHydrophobicityMap.size() != 20) {
        // Sanity check -> expected a file with info for 20 amino acids!
        throw nullptr;
    }

}

std::unordered_map<std::string, double> hydrophobicityParser::getAminoAcidHydrophobicityMap(int letter) {
    
    if (letter == 3) {
        return aminoAcidHydrophobicityMap;
    }

    else if (letter == 1) {

        return convertOneToThreeMap(aminoAcidHydrophobicityMap);
    }

    else {
        throw nullptr;
    }
};
