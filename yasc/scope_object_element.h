//
// Created by chan on 2018/4/2.
//

#ifndef YASCFAIRY_SCOPE_OBJECT_ELEMENT_H
#define YASCFAIRY_SCOPE_OBJECT_ELEMENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <jni.h>

class ScopeObjectElement {
private:
    jobject mObject;
    JNIEnv *mEnv;
    const jobjectArray mArr;
public:
    ScopeObjectElement(JNIEnv *env, const jobjectArray arr, int index) : mEnv(env), mArr(arr) {
        if (arr != NULL) {
            mObject = env->GetObjectArrayElement(mArr, index);
        }
    }

    virtual ~ScopeObjectElement() {
        if (mObject != NULL) {
            mEnv->DeleteLocalRef(mObject);
        }
    }

    const jobject getObject() const {
        return mObject;
    }
};

#ifdef __cplusplus
}
#endif

#endif //YASCFAIRY_SCOPE_OBJECT_ELEMENT_H
