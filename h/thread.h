// File: thread.h

#ifndef _thread_h_
#define _thread_h_

#include "SCHEDULE.H"
#include "System.h"
#include "list.h"

typedef unsigned long StackSize;
const StackSize defaultStackSize = 4096;
typedef unsigned int Time; // time, x 55ms
const Time defaultTimeSlice = 2; // default = 2*55ms
typedef int ID;
class PCB; // Kernel's implementation of a user's thread
class List;

class Thread {
    public:
    void start();
    void waitToComplete();
    virtual ~Thread();
    ID getId();
    static ID getRunningId();
    static Thread * getThreadById(ID id);

    protected:
    friend class PCB;
    friend class KernelSem;
    Thread (StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice);
    virtual void run() {}

    private:
    friend class System;
    friend class List;
    PCB* myPCB;
    static ID posID;
    ID id;
    static List list;
};

class LoopThread:public Thread{
    protected:
    friend class System;
    LoopThread(StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice):Thread(stackSize, timeSlice){}
    virtual void run();
};

void dispatch ();
#endif