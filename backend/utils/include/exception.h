//
// Created by gil on 19/02/18.
//

#ifndef ABPYTOOLS_QT_EXCEPTION_H
#define ABPYTOOLS_QT_EXCEPTION_H

#include <exception>
#include <stdexcept>
#include <Python.h>
#include <boost/python.hpp>
//#include <boost/format.hpp>

using namespace boost::python;
using namespace boost;

class ModuleImportException: public std::runtime_error {

public:

    ModuleImportException(): runtime_error("Python import error") {}

    explicit ModuleImportException(std::string msg):runtime_error(msg.c_str()){}

};

class ClassImportException: public std::runtime_error {

public:

    ClassImportException(): runtime_error("Python import class error") {}

    explicit ClassImportException(std::string msg):runtime_error(msg.c_str()){}

};


class PythonAbPyToolsError: public std::runtime_error {

public:

    PythonAbPyToolsError() : runtime_error("AbPyTools Python error") {}

    PythonAbPyToolsError(PyObject *exc, PyObject *val, PyObject *tb) : runtime_error(
            handle_pyerror(exc, val, tb).c_str()) {};

    std::string handle_pyerror(PyObject *exc, PyObject *val, PyObject *tb) {

        object formatted_list, formatted;
        PyErr_Fetch(&exc, &val, &tb);
        handle<> hexc(exc), hval(allow_null(val)), htb(allow_null(tb));
        object traceback(import("traceback"));
        if (!tb) {
            object format_exception_only(traceback.attr("format_exception_only"));
            formatted_list = format_exception_only(hexc, hval);
        }
        else {
            object format_exception(traceback.attr("format_exception"));
            formatted_list = format_exception(hexc, hval, htb);
        }

        formatted = str("\n").join(formatted_list);

        std::string message = extract<std::string>(formatted);

        return message;

    }
};

class FileDoesNotExistException: public std::runtime_error {

public:

    FileDoesNotExistException(): runtime_error("Could not find file!") {}

    explicit FileDoesNotExistException(std::string msg): runtime_error(msg.c_str()) {}

};

#endif //ABPYTOOLS_QT_EXCEPTION_H
