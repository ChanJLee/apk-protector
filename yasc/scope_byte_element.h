//
// Created by chan on 2018/4/2.
//

#ifndef YASCFAIRY_SCOPE_BYTE_ELEMENT_H
#define YASCFAIRY_SCOPE_BYTE_ELEMENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <jni.h>

class ScopeByteElement {
private:
    jbyte * mBytes;
    JNIEnv *mEnv;
    const jbyteArray mArr;
public:
    ScopeByteElement(JNIEnv *env, const jbyteArray arr) : mEnv(env), mArr(arr) {
        if (arr != NULL) {
            mBytes = env->GetByteArrayElements(mArr, 0);
        }
    }

    virtual ~ScopeByteElement() {
        if (mBytes != NULL) {
            mEnv->ReleaseByteArrayElements(mArr, mBytes, 0);
        }
    }

    const jbyte * getBytes() const {
        return mBytes;
    }
};

#ifdef __cplusplus
}
#endif


#endif //YASCFAIRY_SCOPE_BYTE_ELEMENT_H
