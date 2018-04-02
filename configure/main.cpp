//
// Created by chan on 2018/3/30.
//

#include "c.h"
#include "../yasc/BayRandom.h"
#include "../yasc/CodeTree.h"
#include"Bays4.h"
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
    std::cout << "static const char *pkg_md5_map[][2] = {";
    bays4::Base64 base64;
    for (const char **pkg_md5_entry : pkg_md5_map) {
        std::cout << "{\"" << base64.e(std::string(pkg_md5_entry[0]))
                  << "\",\""
                  << base64.e(std::string(pkg_md5_entry[1]))
                  << "\"},";
    }

    std::cout << "};" << std::endl;
    return 0;
}