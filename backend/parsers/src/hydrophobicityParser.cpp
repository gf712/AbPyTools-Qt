//
// Created by gil on 22/02/18.
//

#include "hydrophobicityParser.h"
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>


std::vector<std::string> aaList{"ALA", "ARG", "ASN", "ASP", "CYS", "GLN", "GLU",
                                "GLY", "HIS", "ILE", "LEU", "LYS", "MET", "PHE",
                                "PRO", "SER", "THR", "TRP", "TYR", "VAL"};

hydrophobicityParser::hydrophobicityParser(std::string &filepath_) {

    if (!boost::filesystem::exists(filepath_)) {
        // write exception
        throw 1;
    }

    // get absolute file path just to be on the safe side..
    filepath = boost::filesystem::canonical(filepath_).string();
}

void hydrophobicityParser::parse() {

    boost::filesystem::ifstream file(filepath);

    int nAminoAcids = 0;

    for (std::string line; std::getline(file, line); )
    {

        // process "line"
        // if line startswith "!" it's just a comment
        std::string commentChar = "!";

        std::cout << "COMPARE: " << line.compare(0, 1, commentChar) << "\n";

        if (line.compare(0, 1, commentChar) != 0) {

            std::cout << line << "\n";
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
            catch (boost::bad_lexical_cast &) {
            // error whilst trying to extract double from string
                throw 1;
            }

            aminoAcidHydrophobicityMap[elements[0]] = numericHValue;

            nAminoAcids++;
        }
    }

    if (nAminoAcids!=20) {
        // Sanity check -> expected a file with info for 20 amino acids!
        throw 1;
    }

}
