LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := yasc

LOCAL_SRC_FILES := \
	BayRandom.cc \
	Bays4.cc \
	CodeTree.cc \
	md5.cpp \
	yarc.cpp \

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
    $(LOCAL_PATH)\build \

LOCAL_CFLAGS += -fexceptions
LOCAL_CFLAGS += -std=c++11
LOCAL_CFLAGS += -fvisibility=hidden

APP_STL := stlport_static

LOCAL_LDLIBS += -L$(SYSROOT)/usr/lib -llog

include $(BUILD_SHARED_LIBRARY)