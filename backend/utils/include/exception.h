//
// Created by gil on 19/02/18.
//

#ifndef ABPYTOOLS_QT_EXCEPTION_H
#define ABPYTOOLS_QT_EXCEPTION_H

#include <exception>
#include <stdexcept>

class ModuleImportException: public std::runtime_error {

public:

    ModuleImportException(): runtime_error("Python import error") {}

    explicit ModuleImportException(std::string msg):runtime_error(msg.c_str()){}

};

#endif //ABPYTOOLS_QT_EXCEPTION_H
