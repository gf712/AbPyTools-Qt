//
// Created by gil on 28/02/18.
//

#include "../include/fastaParser.h"
#include <set>


void FastaParser::parse() {

    boost::filesystem::ifstream file(getFilepath());

    bool expectingSequence = false;

    for (std::string line; std::getline(file, line);) {

        if (ParserRules(line) and !expectingSequence) {
            // this is the name of the entry -> remove '>'
            names.push_back(line.substr(1, line.size()));
            expectingSequence = true;
            Parser::totalEntries++;
        }

        else if (expectingSequence) {
            sequences.push_back(line);
            expectingSequence = false;
        }

        else {
            throw line;
        }
    }

    std::cout << sequences.size() << ' ' << names.size();

    if (sequences.size() != names.size())
        throw printf(
                "Expected the same number of sequences and indentifiers! Got %i names and %i sequences",
                static_cast<int>(names.size()), static_cast<int>(sequences.size()));

}


bool FastaParser::ParserRules(std::string line) {

    std::set<char> aminoAcids ({'A', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'K', 'L',
                                'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'V', 'W', 'Y'});

    if (line[0] == '>' or aminoAcids.find(line.at(0)) != aminoAcids.end()) {
        return true;
    }
    else
        return false;

}