//
// Created by gil on 15/03/18.
//

#include "connection_check.h"

bool abnumConnection() {

    std::string base_command = "timeout 0.2 ping -c ";
    std::string max_attempts = "1";
    std::string url = " www.google.com";
    std::string mode = "r";
    FILE *in;

    std::string command = base_command + max_attempts + url + " 2>%1";
    in = popen(command.c_str(), mode.c_str());

    // returns false if command fails
    if (!in) return false;

    int exit_code = pclose(in);

    // returns true if exit code is 0, else false
    return exit_code == 0;
}
