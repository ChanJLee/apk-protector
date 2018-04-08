//
// Created by chan on 2018/3/30.
//

#include "c.h"
#include "../yasc/BayRandom.h"
#include "../yasc/CodeTree.h"
#include"Bays4.h"
#include <iostream>
#include <string>
#include <fstream>

bays4::Base64 base64;
void write_str(std::ofstream& os, const char* name, const char* content) {
    os << "static const std::string " << name << " =\""
        << base64.e(content)
        << "\";" << std::endl;
}

int main(int argc, char *argv[]) {
    std::cout << "start write: " << argv[1] << std::endl;
    std::ofstream os(argv[1], std::ios::out);

    os  << "#ifndef YASCFAIRY_C_H" << std::endl
        << "#define YASCFAIRY_C_H" << std::endl
        << "#include<string>" << std::endl
        << "#ifdef __cplusplus" << std::endl
        << "extern \"C\" {" << std::endl
        << "#endif" << std::endl;

    os << "static const char *pkg_md5_map[][2] = {";

    for (const char **pkg_md5_entry : pkg_md5_map) {
        std::cout << "write " << pkg_md5_entry[0] << " " << pkg_md5_entry[1] << std::endl;
        os << "{\"" << base64.e(std::string(pkg_md5_entry[0]))
                  << "\",\""
                  << base64.e(std::string(pkg_md5_entry[1]))
                  << "\"}," << std::endl;
    }

    os << "};" << std::endl;

    std::cout << "write const" << std::endl;
    write_str(os, "GET_MD5_FUNC_DESCRIPTION", "(Ljava/lang/String;)Ljava/lang/String;");
    write_str(os, "GET_P_FUNC_DESCRIPTION", "(Landroid/content/Context;)Ljava/lang/String;");
    write_str(os, "CLASS_PATH_UTILITIES", "com/shanbay/yasc/Utilities");
    write_str(os, "UTILITIS_WRITE_ALL", "writeAll");
    write_str(os, "UTILITIS_WRITE_ALL_DESCRIPTION", "(Landroid/content/Context;Ljava/lang/String;Ljava/lang/String;)V");
    write_str(os, "LIB_FUNC", "make_big_news");
    write_str(os, "LIB_NAME", "/libpoker.so");
    write_str(os, "CLASS_PATH_YASC", "com/shanbay/yasc/Yasc");
    write_str(os, "CLASS_PATH_ACTIVITY_THREAD", "android/app/ActivityThread");
    write_str(os, "ACTIVITY_THREAD_CURRENT_APPLICATION", "currentApplication");
    write_str(os, "ACTIVITY_THREAD_CURRENT_APPLICATION_DESCRIPTION", "()Landroid/app/Application;");
    write_str(os, "CONTEXT_GET_PACKAGE_MANAGER", "getPackageManager");
    write_str(os, "CONTEXT_GET_PACKAGE_MANAGER_DESCRIPTION", "()Landroid/content/pm/PackageManager;");
    write_str(os, "PACKAGE_MANAGER_GET_PACKAGE_INFO", "getPackageInfo");
    write_str(os, "PACKAGE_MANAGER_GET_PACKAGE_INFO_DESCRIPTION", "(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;");
    write_str(os, "PACKAGE_INFO_SIGNATURES", "signatures");
    write_str(os, "PACKAGE_INFO_SIGNATURES_DESCRIPTION", "[Landroid/content/pm/Signature;");
    write_str(os, "PACKAGE_INFO_SIGNATURES_TO_CHARS_STRING", "toByteArray");
    write_str(os, "PACKAGE_INFO_SIGNATURES_TO_CHARS_STRING_DESCRIPTION", "()[B");
    write_str(os, "CONTEXT_GET_PACKAGE_NAME", "getPackageName");
    write_str(os, "CONTEXT_GET_PACKAGE_NAME_DESCRIPTION", "()Ljava/lang/String;");

    // make big news
    write_str(os, "WRITE_ALL", "writeAll");
    write_str(os, "WRITE_ALL_DESCRIPTION", "(Landroid/content/Context;Ljava/lang/String;Ljava/lang/String;)V");
    write_str(os, "POKER", "resources/sound_poker.wav");
    write_str(os, "MAKE_BIG_NEWS", "make_big_news");
    write_str(os, "GET_DIR", "getDir");
    write_str(os, "GET_DIR_DESCRIPTION", "(Ljava/lang/String;I)Ljava/io/File;");
    write_str(os, "DEST_LIB", "libs");
    write_str(os, "GET_ABSOLUTE_PATH", "getAbsolutePath");
    write_str(os, "GET_ABSOLUTE_PATH_DESCRIPTION", "()Ljava/lang/String;");
    write_str(os, "DEST_NAME", "/libpoker.so");

    write_str(os, "DEFAULT_SIGNATURE", "c1deb2230c24a502046f6a31766445c2");

    os  << "#ifdef __cplusplus" << std::endl
        << "}" << std::endl
        << "#endif" << std::endl
        << "#endif //YASCFAIRY_C_H" << std::endl;
    os.close();
    return 0;
}