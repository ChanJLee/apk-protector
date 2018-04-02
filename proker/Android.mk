LOCAL_PATH := $(call my-dir)  
include $(CLEAR_VARS)  
LOCAL_MODULE := poker  

LOCAL_SRC_FILES := poker.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)

LOCAL_CFLAGS += -fexceptions

include $(BUILD_SHARED_LIBRARY) 