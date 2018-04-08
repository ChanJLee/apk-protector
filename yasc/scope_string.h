//
// Created by chan on 2018/3/26.
//

#ifndef YASCFAIRY_SCOPE_STRING_H
#define YASCFAIRY_SCOPE_STRING_H

#ifdef __cplusplus
extern "C" {
#endif

#include <jni.h>

class ScopeString {
private:
    JNIEnv *mEnv;
    const jstring mJString;
    const char *mCString;

public:
    ScopeString(JNIEnv *env, const jstring str) : mEnv(env), mJString(str) {
        if (mJString != NULL) {
            mCString = mEnv->GetStringUTFChars(mJString, 0);
        }
    }

    virtual ~ScopeString() {
        if (mCString != NULL) {
            mEnv->ReleaseStringUTFChars(mJString, mCString);
        }
    }

    const char *getCString() const {
        return mCString;
    }

    const jstring getJString() const {
        return mJString;
    }
};

#ifdef __cplusplus
}
#endif

#endif //YASCFAIRY_SCOPE_STRING_H
