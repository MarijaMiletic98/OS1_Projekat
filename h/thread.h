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
volatile PCB* running;

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
    Thread (StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice);
    virtual void run() {}

    private:
    friend class System;
    PCB* myPCB;
    static ID posID;
    ID id;
    static List list;
};

class LoopThread:public Thread{
    protected:
    virtual void run(){
        while(1);
    }
}

void dispatch ();
#endif