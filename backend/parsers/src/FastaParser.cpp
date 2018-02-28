//
// Created by gil on 28/02/18.
//

#include "../include/fastaParser.h"
#include <iostream>

void FastaParser::parse() {

    boost::filesystem::ifstream file(getFilepath());
    std::string nameChar = ">";
    bool expectingSequence = false;

    for (std::string line; std::getline(file, line);) {

        if (line.compare(0, 1, nameChar) == 0 and !expectingSequence) {

            // this is the name of the entry -> remove ">"
            names.push_back(line.substr(1, line.size()));
            expectingSequence = true;

        }

        else if (expectingSequence) {

            sequences.push_back(line);
            expectingSequence = false;

        }

        else {
            throw line;
        }
    }

    std::cout << sequences.size() << " " << names.size();

    if (sequences.size() != names.size())
        throw printf(
                "Expected the same number of sequences and indentifiers! Got %i names and %i sequences",
                static_cast<int>(names.size()), static_cast<int>(sequences.size()));

}