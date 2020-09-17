#ifndef _semlist_h_
#define _semlist_h_

#include "kernelsm.h"

class KernelSem;

class SemaphoreList{
    public:
    SemaphoreList();
    void add(KernelSem* k);
    void checkTime();
    virtual ~SemaphoreList();

    private:
    struct Elem{
        KernelSem* semaphore;
        Elem* next;
        Elem(KernelSem* s, Elem* n):semaphore(s), next(n){}
    };
    Elem* head, *last;
};
#endif