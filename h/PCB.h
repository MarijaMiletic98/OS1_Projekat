#ifndef _thread_h_
#define _thread_h_

#include "thread.h"

class PCB{
    public:
    static void wrapper();
    PCB(StackSize sSize, Time tmSlc, Thread* myth);
    virtual ~PCB();

    private:
    friend class Thread;
    friend class System;
    unsigned ss, sp;
    StackSize stackSize;
    Time timeSlice;
    unsigned* stack;
    Thread* myThread;
    unsigned blocked;
    unsigned finished;
    List* blockedOnMe;
};
#endif