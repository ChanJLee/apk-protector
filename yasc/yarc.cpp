//
// Created by caspar on 6/23/16.
//
#ifdef __cplusplus
extern "C" {
#endif

const char SO_FILE_VERSION[]  __attribute__ ((section (".bugly_version"))) = "<1.1.0>";

#ifdef __cplusplus
}
#endif

#include <stdlib.h>
#include <string.h>
#include <jni.h>
#include <stdio.h>
#include <dirent.h>
#include "yarc.h"
#include <sstream>
#include <sys/types.h>
#include <unistd.h>
#include "c.h"
#include "Bays4.h"
#include <dlfcn.h>
#include "scope_dy_lib.h"
#include "scope_malloc.h"

// #ifdef ENV_DEBUG
// #include "3rd/LeakTracer/libleaktracer/include/MemoryTrace.hpp"
// #endif

#ifdef __cplusplus
extern "C" {
#endif

#include "md5.h"

#ifdef __cplusplus
}
#endif

static bays4::Base64 base64;

typedef void (*handle)(int);

jstring get_package(JNIEnv *env, jobject context_object);

jstring get_package_from_android(JNIEnv *env, jobject context_object);

jstring get_package_from_cmdline(JNIEnv *env);

int check_app_signature(JNIEnv *env, jobject context_object);

jobject get_context_object(JNIEnv *env);

void get_md5(const void *payload, size_t len, char *md5);

int register_all_func(JNIEnv *env);

void make_big_news(JNIEnv *env, jobject context_object, int sig);

std::string get_lib_dir(JNIEnv *env, jobject context_object);

jint JNI_OnLoad(JavaVM *vm, void *) {
    JNIEnv *env = NULL;
    if (vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK) {
        return -1;
    }

    // #ifdef ENV_DEBUG
    // leaktracer::MemoryTrace::GetInstance().startMonitoringAllThreads();
    // #endif

    if (register_all_func(env) < 0) {
        return -1;
    }

    DEFINE_REF(jobject, context_object, env, get_context_object(env));
    int result = check_app_signature(env, context_object);

    // #ifdef ENV_DEBUG
    // leaktracer::MemoryTrace::GetInstance().stopAllMonitoring();
    // LOGD("To writeLeaksToFile %s.", "/sdcard/leaks.out");
    // leaktracer::MemoryTrace::GetInstance().writeLeaksToFile("/sdcard/leaks.out");
    // #endif

    LOGD("check result: %d", result);
    if (result == 0) {
        LOGD("pass");
        return JNI_VERSION_1_6;
    }

    if (result == ERROR_RUNTIME) {
        LOGE("check signature failure");
        return JNI_VERSION_1_6;
    }

    make_big_news(env, context_object, result);
    return JNI_VERSION_1_6;
}

void make_big_news(JNIEnv *env, jobject context_object, int sig) {
    const std::string& dest_path = get_lib_dir(env, context_object);
    const std::string& utilities_class_path = base64.d(CLASS_PATH_UTILITIES);
    DEFINE_REF(jclass, utils_class, env, env->FindClass(utilities_class_path.c_str()));

    const std::string& write_all = base64.d(WRITE_ALL);
    const std::string& write_all_description = base64.d(WRITE_ALL_DESCRIPTION);
    const std::string& poker = base64.d(POKER);

    jmethodID methodId = env->GetStaticMethodID(utils_class, write_all.c_str(), write_all_description.c_str());
    DEFINE_STR(src, env, env->NewStringUTF(poker.c_str()));
    DEFINE_STR(dest, env, env->NewStringUTF(dest_path.c_str()));

    env->CallStaticVoidMethod(utils_class, methodId, context_object, src_scope_str.getJString(), dest_scope_str.getJString());

    ScopeLib scopeLib(dest_path.c_str(), RTLD_LAZY);
    void* dy_lib = scopeLib.getLib();
    if (dy_lib == NULL) {
        LOGE("open lib failure");
        return;
    }

    dlerror();

    const std::string& make_big_news = base64.d(MAKE_BIG_NEWS);
    handle func = (handle) dlsym(dy_lib, make_big_news.c_str());
    if (func) {
        LOGD("find make big news success");
    }

    func(sig);
}

std::string get_lib_dir(JNIEnv *env, jobject context_object) {
    LOGD("call getDir");
    DEFINE_REF(jclass, context_class, env, env->GetObjectClass(context_object));
    const std::string& get_dir = base64.d(GET_DIR);
    const std::string& get_dir_description = base64.d(GET_DIR_DESCRIPTION);
    jmethodID methodId = env->GetMethodID(context_class, get_dir.c_str(),
                                             get_dir_description.c_str());

    const std::string& libs_name = base64.d(DEST_LIB);
    DEFINE_REF(jstring, dir_name, env, env->NewStringUTF(libs_name.c_str()));
    DEFINE_REF(jobject, dir_file, env, env->CallObjectMethod(context_object, methodId, dir_name, 0));

    LOGD("call getAbsolutePath");
    const std::string& get_absolute_path = base64.d(GET_ABSOLUTE_PATH);
    const std::string& get_absolute_path_description = base64.d(GET_ABSOLUTE_PATH_DESCRIPTION);
    DEFINE_REF(jclass, file_class, env, env->GetObjectClass(dir_file));
    methodId = env->GetMethodID(file_class, get_absolute_path.c_str(),
                                                 get_absolute_path_description.c_str());

    DEFINE_STR(dir_path, env, (jstring) env->CallObjectMethod(dir_file, methodId));
    LOGD("dest path: %s", dir_path);

    const std::string& dest_name = base64.d(DEST_NAME);
    std::stringstream so_dest_path;
    so_dest_path << dir_path
                 << dest_name;
    return so_dest_path.str();
}

int register_all_func(JNIEnv *env) {
    JNINativeMethod methods[] = {
        {JAVA_FUNC(FUNC_getMd5), NULL, (void *) &JNI_FUNC(
                FUNC_getMd5)},
        {JAVA_FUNC(
                 FUNC_getP), NULL, (void *) &JNI_FUNC(
                FUNC_getP)}
    };
    
    const std::string& md5_str = base64.d(GET_MD5_FUNC_DESCRIPTION);
    methods[0].signature = md5_str.c_str();

    const std::string& p_str = base64.d(GET_P_FUNC_DESCRIPTION);
    methods[1].signature = p_str.c_str();

    int len = sizeof(methods) / sizeof(JNINativeMethod);
    const std::string& yasc_class_path = base64.d(CLASS_PATH_YASC);
    DEFINE_REF(jclass, clazz, env, env->FindClass(yasc_class_path.c_str()));
    return env->RegisterNatives(clazz, methods, len);
}

jobject get_context_object(JNIEnv *env) {
    const std::string& activity_thread_class_path = base64.d(CLASS_PATH_ACTIVITY_THREAD);
    DEFINE_REF(jclass, activity_thread, env, env->FindClass(activity_thread_class_path.c_str()));
    if (activity_thread == NULL) {
        return NULL;
    }

    const std::string& current_application = base64.d(ACTIVITY_THREAD_CURRENT_APPLICATION);
    const std::string& current_application_description = base64.d(ACTIVITY_THREAD_CURRENT_APPLICATION_DESCRIPTION);
    jmethodID methodID = env->GetStaticMethodID(activity_thread, current_application.c_str(),
                                                current_application_description.c_str());
    if (methodID == NULL) {
        return NULL;
    }

    return (env)->CallStaticObjectMethod(activity_thread, methodID);
}

int check_app_signature(JNIEnv *env, jobject context_object) {
    if (context_object == NULL) {
        return ERROR_RUNTIME;
    }

    DEFINE_REF(jclass, context_class, env, env->GetObjectClass(context_object));

    //context.getPackageManager()
    const std::string& get_package_manager = base64.d(CONTEXT_GET_PACKAGE_MANAGER);
    const std::string& get_package_manager_description = base64.d(CONTEXT_GET_PACKAGE_MANAGER_DESCRIPTION);
    jmethodID methodId = env->GetMethodID(context_class, get_package_manager.c_str(),
                                          get_package_manager_description.c_str());
    DEFINE_REF(jobject, package_manager_object, env,
               env->CallObjectMethod(context_object, methodId));
    if (package_manager_object == NULL) {
        return ERROR_RUNTIME;
    }

    jstring package_name_string = get_package(env, context_object);
    if (package_name_string == NULL) {
        return ERROR_RUNTIME;
    }

    DEFINE_STR(pkg_name, env, package_name_string);
    LOGD("current package name: %s", pkg_name);

    //PackageManager.getPackageInfo()
    const std::string& get_package_info = base64.d(PACKAGE_MANAGER_GET_PACKAGE_INFO);
    const std::string& get_package_info_description = base64.d(PACKAGE_MANAGER_GET_PACKAGE_INFO_DESCRIPTION);
    DEFINE_REF(jclass, package_manager_class, env, env->GetObjectClass(package_manager_object));
    methodId = env->GetMethodID(package_manager_class, get_package_info.c_str(),
                                get_package_info_description.c_str());

    DEFINE_REF(jobject, package_info_object, env,
               env->CallObjectMethod(package_manager_object, methodId,
                                     package_name_string, 64));
    if (package_info_object == NULL) {
        LOGE("fetch package info failure");
        return ERROR_RUNTIME;
    }

    //PackageInfo.signatures[0]
    const std::string& signatures = base64.d(PACKAGE_INFO_SIGNATURES);
    const std::string& signatures_description = base64.d(PACKAGE_INFO_SIGNATURES_DESCRIPTION);
    DEFINE_REF(jclass, package_info_class, env, env->GetObjectClass(package_info_object));
    jfieldID fieldId = env->GetFieldID(package_info_class, signatures.c_str(),
                                       signatures_description.c_str());
    DEFINE_REF(jobjectArray, signature_object_array, env,
               (jobjectArray) env->GetObjectField(package_info_object, fieldId));
    if (signature_object_array == NULL) {
        LOGE("fetch signature failure");
        return ERROR_RUNTIME;
    }

    DEFINE_REF(jobject, signature_object, env,
               env->GetObjectArrayElement(signature_object_array, 0));

    //Signature.toCharsString()
    const std::string& to_byte_array = base64.d(PACKAGE_INFO_SIGNATURES_TO_CHARS_STRING);
    const std::string& to_byte_array_description = base64.d(PACKAGE_INFO_SIGNATURES_TO_CHARS_STRING_DESCRIPTION);
    DEFINE_REF(jclass, signature_class, env, env->GetObjectClass(signature_object));
    methodId = env->GetMethodID(signature_class, to_byte_array.c_str(), to_byte_array_description.c_str());
    DEFINE_REF(jbyteArray, signature, env,
               (jbyteArray) env->CallObjectMethod(signature_object, methodId));
    jsize len = env->GetArrayLength(signature);
    DEFINE_BYTE_ELEMENT(bytes, env, signature);

    char md5[MD5_LEN] = {0};
    get_md5(bytes, static_cast<u4>(len), md5);
    LOGD("current md5: %s", md5);
    const std::string& default_md5 = base64.d(DEFAULT_SIGNATURE);
    if (strcmp(md5, default_md5.c_str()) == 0) {
        return 0;
    }

    for (const char **map_entry : pkg_md5_map) {
        if (!strcmp(base64.d(map_entry[0]).c_str(), pkg_name)) {
            return strcmp(base64.d(map_entry[1]).c_str(), md5) ? ERROR_RESIGNATURE : 0;
        }
    }

    return ERROR_REPACKAGE;
}

IMPL_FUNC(jstring, FUNC_getP, jobject context_object) {
    return get_package(env, context_object);
}

jstring get_package(JNIEnv *env, jobject context_object) {
    jstring pkg = get_package_from_android(env, context_object);
    if (pkg) {
        return pkg;
    }

    return get_package_from_cmdline(env);
}

jstring get_package_from_android(JNIEnv *env, jobject context_object) {
    DEFINE_REF(jclass, context_class, env, env->GetObjectClass(context_object));

    //context.getPackageManager()
     const std::string& get_package_manager = base64.d(CONTEXT_GET_PACKAGE_MANAGER);
    const std::string& get_package_manager_description = base64.d(CONTEXT_GET_PACKAGE_MANAGER_DESCRIPTION);
    jmethodID methodId = env->GetMethodID(context_class, get_package_manager.c_str(),
                                          get_package_manager_description.c_str());
    DEFINE_REF(jobject, package_manager_object, env,
               env->CallObjectMethod(context_object, methodId));
    if (package_manager_object == NULL) {
        return NULL;
    }

    //context.getPackageName()
    const std::string& get_package_name = base64.d(CONTEXT_GET_PACKAGE_NAME);
    const std::string& get_package_name_description = base64.d(CONTEXT_GET_PACKAGE_NAME_DESCRIPTION);
    methodId = env->GetMethodID(context_class, get_package_name.c_str(), get_package_name_description.c_str());
    const jstring package_name_string = (jstring) env->CallObjectMethod(context_object, methodId);
    if (package_name_string == nullptr) {
        LOGE("fetch package name failure");
        return NULL;
    }

    DEFINE_STR(pkg_name, env, package_name_string);
    LOGD("current package name: %s", pkg_name);
    return package_name_string;
}

jstring get_package_from_cmdline(JNIEnv *env) {
    pid_t pid = getpid();
    DIR *proc_dir = NULL;
    if ((proc_dir = opendir("/proc")) == NULL) {
        return NULL;
    }

    struct dirent *entry = NULL;
    jstring result = NULL;
    while ((entry = readdir(proc_dir)) != NULL) {
        if (strcmp(entry->d_name, "self") == 0) {
            continue;
        }

        if (atoi(entry->d_name) != pid) {
            continue;
        }

        std::ostringstream cmd_file_name_os;
        cmd_file_name_os << "/proc/" << entry->d_name << "/cmdline";
        std::string cmd_file_name = cmd_file_name_os.str();
        FILE *cmd_file = fopen(cmd_file_name.c_str(), "r");
        if (cmd_file == NULL) {
            continue;
        }

        char cmd_file_content[128] = {0};
        fscanf(cmd_file, "%s", cmd_file_content);
        fclose(cmd_file);
        sscanf(cmd_file_content, "%[^:]", cmd_file_content);
        result = env->NewStringUTF(cmd_file_content);
    }

    closedir(proc_dir);
    return result;

}

IMPL_FUNC(jstring, FUNC_getMd5, jstring text) {
    DEFINE_STR(str, env, text)

    char md5[MD5_LEN] = {0};
    get_md5(str, strlen(str), md5);

    return env->NewStringUTF(md5);
}

void get_md5(const void *data, size_t len, char *md5) {
    MD5_CTX context = {0};
    MD5_Init(&context);
    MD5_Update(&context, data, len);
    u1 dest[RAW_MD5_LEN] = {0};
    MD5_Final(dest, &context);

    for (int i = 0; i < RAW_MD5_LEN; i++) {
        sprintf(md5, "%s%02x", md5, dest[i]);
    }
}