#ifndef _pcb_h_
#define _pcb_h_

#include "thread.h"
#include "list.h"
#include "System.h"
#include "SCHEDULE.H"

typedef unsigned int Time; // time, x 55ms
typedef unsigned long StackSize;

class Thread;
class List;

class PCB{
    public:
    static void wrapper();
    PCB(StackSize sSize, Time tmSlc, Thread* myth);
    virtual ~PCB();

    private:
    friend class Thread;
    friend class System;
    friend class KernelSem;
    friend class List;
    friend class Event;
    unsigned ss, sp, bp;
    StackSize stackSize;
    Time timeSlice;
    unsigned unblockedAfterTime;
    unsigned* stack;
    Thread* myThread;
    unsigned blocked;
    unsigned finished;
    List* blockedOnMe;
    static volatile PCB* running;
};
#endif