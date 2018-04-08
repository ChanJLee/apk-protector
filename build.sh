#!/usr/bin/env bash

current_dir=`pwd`

echo "make poker"
cd proker
make all
mv libs/armeabi-v7a/libpoker.so ../lib/src/main/assets/resources/sound_poker.wav
cd -

echo "configure"
cd configure

make all
chmod +x main

c_h="${current_dir}/yasc/c.h"
rm ${c_h}
./main ${c_h}
make clean
cd -

cd yasc
echo "make yasc"
make all
rm -rf  ../lib/src/main/jniLibs/armeabi-v7a
mkdir -p ../lib/src/main/jniLibs/armeabi-v7a
mv libs/armeabi-v7a ../lib/src/main/jniLibs/
cd -

./gradlew clean -offline
./gradlew assumbleRelease -offline