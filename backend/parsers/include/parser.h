//
// Created by gil on 28/02/18.
//

#ifndef ABPYTOOLS_QT_PARSER_H
#define ABPYTOOLS_QT_PARSER_H

#include "abpytools_exceptions.h"
#include <boost/filesystem/operations.hpp>
#include <iostream>
#include <string>

class Parser {

public:

    Parser(std::string filepath_);
    virtual ~Parser() {};

    virtual bool ParserRules(std::string line) {totalLines++; return true;}

    std::string getFilepath() { return filepath;}
    std::string getBasename() { return basename;}
    int getTotalLines() {return totalLines;}

private:
    std::string filepath;
    std::string basename;

protected:
    int totalLines;

};


#endif //ABPYTOOLS_QT_PARSER_H
