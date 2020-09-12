#include "PCB.h"
#include "thread.h"
#include <dos.h>

volatile PCB* PCB::running=NULL;

PCB::PCB(StackSize sSize, Time tmSlc, Thread* myth):stackSize(sSize/2), timeSlice(tmSlc), myThread(myth), blocked(0), finished(0){ 
    if(stackSize!=0){
        stack=new unsigned[stackSize];
        stack[stackSize-1]=0x200;
        stack[stackSize-2]=FP_SEG(wrapper);
        stack[stackSize-3]=FP_OFF(wrapper);

        ss=FP_SEG(stack+stackSize-12);
        bp=sp=FP_OFF(stack+stackSize-12);

        blockedOnMe=new List();
    }
}

void PCB::wrapper(){
    running->myThread->run();

    lock
    cout<<flush;
    running->finished=1;
    Thread* t=running->blockedOnMe->removeFirst();
    while(t){
        t->myPCB->blocked=0;
        Scheduler::put(t->myPCB);
        t=running->blockedOnMe->removeFirst();
    }
    unlock
    dispatch();
}

PCB::~PCB(){
    if(stackSize!=0){
        delete[] stack;
        delete blockedOnMe;
    }
}