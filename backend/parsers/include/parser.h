//
// Created by gil on 28/02/18.
//

#ifndef ABPYTOOLS_QT_PARSER_H
#define ABPYTOOLS_QT_PARSER_H

#include <abpytools_exceptions.h>
#include <boost/filesystem/operations.hpp>
//#include <boost/filesystem/convenience.hpp>

class Parser {

public:
    Parser(std::string filepath_);

    std::string getFilepath() { return filepath;}
    std::string getBasename() { return basename;}

private:
    std::string filepath;
    std::string basename;

};


#endif //ABPYTOOLS_QT_PARSER_H
