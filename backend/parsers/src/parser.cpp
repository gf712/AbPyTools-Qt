//
// Created by gil on 28/02/18.
//

#include "../include/parser.h"

Parser::Parser(std::string filepath_) {

    if (!boost::filesystem::exists(filepath_)) {
    // write exception
        throw FileDoesNotExistException("Unknown filepath: " + boost::filesystem::canonical(filepath_).string());
    }

    // get absolute file path just to be on the safe side..
    filepath = boost::filesystem::canonical(filepath_).string();

    // store basename
    basename = boost::filesystem::path(filepath_).stem().string();
}