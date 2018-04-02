LOCAL_ARM_MODE := armeabi-v7a

all: check clean build

check:
ifeq (, $(shell which ndk-build))
        $(error "No 'ndk-build' in PATH, please install Android NDK and configure properly")
endif

build:
	ndk-build APP_ABI="armeabi-v7a" NDK_PROJECT_PATH=. APP_BUILD_SCRIPT=./Android.mk NDK_APPLICATION_MK=./Application.mk

clean:
	rm -rf *.c~
	rm -rf *.h~
	rm -rf obj/
	rm -rf libs/

install:
	adb push libs/armeabi-v7a/libpoker.so /sdcard/libpoker.so