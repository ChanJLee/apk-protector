//
// Created by chan on 2018/3/26.
//

#ifndef YASCFAIRY_SCOPE_MALLOC_H
#define YASCFAIRY_SCOPE_MALLOC_H

template <class T>
class ScopeMalloc {
private:
    T* mRef;

public:
    ScopeMalloc(T* ref) : mRef(ref) {
    }

    virtual ~ScopeMalloc() {
        if (mRef != NULL) {
            delete mRef;
        }
    }
};

#endif //YASCFAIRY_SCOPE_STRING_H
