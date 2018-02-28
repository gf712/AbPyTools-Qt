//
// Created by gil on 28/02/18.
//

#ifndef ABPYTOOLS_QT_PARSER_H
#define ABPYTOOLS_QT_PARSER_H

#include <exception.h>
#include <boost/filesystem/operations.hpp>

class Parser {

public:
    Parser(std::string filepath_);

    std::string getFilepath() { return filepath;}

private:
    std::string filepath;

};


#endif //ABPYTOOLS_QT_PARSER_H
