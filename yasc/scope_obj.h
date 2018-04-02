//
// Created by chan on 2018/3/26.
//

#ifndef YASCFAIRY_SCOPE_OBJ_H
#define YASCFAIRY_SCOPE_OBJ_H

#include <jni.h>

template<typename Ref>
class ScopeLocalRef {
private:
    JNIEnv *mEnv;
    const Ref mRef;

public:
    ScopeLocalRef(JNIEnv *env, const Ref ref) : mEnv(env), mRef(ref) {
    }

    virtual ~ScopeLocalRef() {
        if (mRef) {
            mEnv->DeleteLocalRef(mRef);
        }
    }
};


#endif //YASCFAIRY_SCOPE_OBJ_H
