//
// Created by chan on 2018/3/30.
//

#ifndef YASCFAIRY_SCOPEDYLIB_H
#define YASCFAIRY_SCOPEDYLIB_H


#ifdef __cplusplus
extern "C" {
#endif

#include <dlfcn.h>

class ScopeLib {
private:
    void* mHandle;

public:
    ScopeLib(const char* filename, int flags) {
        mHandle = dlopen(filename, flags);
    }

    virtual ~ScopeLib() {
        if (mHandle) {
            dlclose(mHandle);
        }
    }

    void* getLib() {
        return mHandle;
    }
};

#ifdef __cplusplus
}
#endif

#endif //YASCFAIRY_SCOPEDYLIB_H
