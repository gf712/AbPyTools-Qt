//
// Created by gil on 28/02/18.
//

#ifndef ABPYTOOLS_QT_FASTAPARSER_H
#define ABPYTOOLS_QT_FASTAPARSER_H

#include "parser.h"
#include <boost/filesystem/fstream.hpp>


class fastaParser: public Parser {

public:

    fastaParser(std::string filepath_): Parser(filepath_) {};
    ~fastaParser() = default;

    void parse();

    std::vector<std::string> getNames() { return names; }
    std::vector<std::string> getSequences() {return sequences; }

private:

    std::vector<std::string> names;
    std::vector<std::string> sequences;

};


#endif //ABPYTOOLS_QT_FASTAPARSER_H
