#!/usr/bin/env bash

# make encode

echo "make encoder"
cd encode

make clean
make build
chmod +x main

pkg_md5_map=`./main`
cd -

echo "configure project"
lib_c="../lib/src/main/cpp/c.h"
echo "#ifndef YASCFAIRY_C_H" > ${lib_c}
echo "#define YASCFAIRY_C_H" >> ${lib_c}
echo "#ifdef __cplusplus" >> ${lib_c}
echo 'extern "C" {' >> ${lib_c}
echo "#endif" >> ${lib_c}
echo ${pkg_md5_map} >> ${lib_c}
echo "#ifdef __cplusplus" >> ${lib_c}
echo "}" >> ${lib_c}
echo "#endif" >> ${lib_c}
echo "#endif //YASCFAIRY_C_H" >> ${lib_c}