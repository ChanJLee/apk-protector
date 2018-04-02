#!/usr/bin/env bash

echo "make proker"
cd proker
make all
cd -

echo "configure"
cd configure

make all
chmod +x main

const_content=`./main`
make clean
cd -

echo "configure project"
lib_c="yasc/c.h"
rm ${lib_c}
echo "#ifndef YASCFAIRY_C_H" > ${lib_c}
echo "#define YASCFAIRY_C_H" >> ${lib_c}
echo "#ifdef __cplusplus" >> ${lib_c}
echo 'extern "C" {' >> ${lib_c}
echo "#endif" >> ${lib_c}
echo ${const_content} >> ${lib_c}
echo "#ifdef __cplusplus" >> ${lib_c}
echo "}" >> ${lib_c}
echo "#endif" >> ${lib_c}
echo "#endif //YASCFAIRY_C_H" >> ${lib_c}


cd yasc
echo "make yasc"
make all
rm -rf  ../lib/src/main/jniLibs/armeabi-v7a
mkdir -p ../lib/src/main/jniLibs/armeabi-v7a
mv libs/armeabi-v7a ../lib/src/main/jniLibs/
cd -