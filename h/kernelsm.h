#ifndef _kernelsm_h_
#define _kernelsm_h_

#include "semaphor.h"
#include "semlist.h"
#include "list.h"

class KernelSem{
    public:
    KernelSem(int i);
    int getValue();
    virtual int wait (Time maxTimeToWait);
    virtual int signal(int n=0);
    virtual ~KernelSem();

    private:
    friend class System;
    friend class SemaphoreList;
    int value;
    List *blocked;
    static SemaphoreList semaphores;
};
#endif