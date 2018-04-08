//
// Created by caspar on 6/23/16.
//

#ifndef YARC_H
#define YARC_H

#include <android/log.h>
#include "scope_obj.h"
#include "scope_string.h"
#include "scope_byte_element.h"
#include "scope_object_element.h"
#include "build/env.h"

#ifdef LOG_TAG
#undef LOG_TAG
#endif

#ifdef ENV_DEBUG
#define  LOG_TAG    "yarc-jni"
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, \
                   __VA_ARGS__))
#define LOGD(...) ((void)__android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, \
                   __VA_ARGS__))
#else
#define LOGE(...) (void*) 0
#define LOGD(...) (void*) 0
#endif

const int ERROR_RUNTIME = -1;
const int ERROR_REPACKAGE = -2;
const int ERROR_RESIGNATURE = -3;

const int RAW_MD5_LEN = 16;
const int MD5_LEN = ((RAW_MD5_LEN) * 2 + 1);

typedef unsigned int u4;
typedef unsigned char u1;

#define FUNC_getP__ getP
#define FUNC_getP FUNC_getP__

#define FUNC_getMd5__ getMd5
#define FUNC_getMd5 FUNC_getMd5__

/* java function name */
#define JAVA_FUNC__(FUNC) #FUNC
#define JAVA_FUNC(FUNC) JAVA_FUNC__(FUNC)

/* jni function name */
#define JNI_FUNC__(FUNC) o0x_0x_ ## FUNC
#define JNI_FUNC(FUNC) JNI_FUNC__(FUNC)

/* define function */
#define DEFINE_FUNC__(RETURN_TYPE, FUNC, ...) \
    extern "C" { \
    JNIEXPORT RETURN_TYPE \
         JNI_FUNC(FUNC) \
            (JNIEnv* env, jobject thiz, ##__VA_ARGS__);\
    }
#define DEFINE_FUNC(RETURN_TYPE, FUNC, ...) DEFINE_FUNC__(RETURN_TYPE, FUNC, ##__VA_ARGS__)

/* implement function */
#define IMPL_FUNC__(RETURN_TYPE, FUNC, ...)  \
    JNIEXPORT RETURN_TYPE \
       JNI_FUNC(FUNC) \
            (JNIEnv* env, jobject thiz, ##__VA_ARGS__)
#define IMPL_FUNC(RETURN_TYPE, FUNC, ...) IMPL_FUNC__(RETURN_TYPE, FUNC, ##__VA_ARGS__)

/* define a reference that needs to be released(Env->DeleteLocalRef(ref)) */
#define DEFINE_REF__(RETURN_TYPE, NAME, ENV, OBJ) \
    RETURN_TYPE NAME = (OBJ); \
    ScopeLocalRef<RETURN_TYPE> NAME ## _ref(ENV, NAME);
#define DEFINE_REF(RETURN_TYPE, NAME, ENV, OBJ) DEFINE_REF__(RETURN_TYPE, NAME, ENV, OBJ)

/* define string */
#define DEFINE_STR__(NAME, ENV, JSTR) \
    ScopeString NAME ## _scope_str(ENV, JSTR); \
    const char* NAME = NAME ## _scope_str.getCString();
#define DEFINE_STR(NAME, ENV, JSTR) DEFINE_STR__(NAME, ENV, JSTR)

#define DEFINE_BYTE_ELEMENT__(NAME, ENV, ARR) \
    ScopeByteElement NAME ## _scope_byte_element(ENV, ARR); \
    const jbyte * NAME = NAME ## _scope_byte_element.getBytes();
#define DEFINE_BYTE_ELEMENT(NAME, ENV, ARR) DEFINE_BYTE_ELEMENT__(NAME, ENV, ARR)

#define DEFINE_OBJECT_ELEMENT__(NAME, ENV, ARR, INDEX) \
    ScopeObjectElement NAME ## _scope_object_element(ENV, ARR, INDEX); \
    const jobject NAME = NAME ## _scope_object_element.getObject();
#define DEFINE_OBJECT_ELEMENT(NAME, ENV, ARR, INDEX) DEFINE_OBJECT_ELEMENT__(NAME, ENV, ARR, INDEX)


/* define function */
DEFINE_FUNC(jstring, FUNC_getMd5, jstring text);
DEFINE_FUNC(jstring, FUNC_getP, jobject context_object);

#endif //YARC_H
