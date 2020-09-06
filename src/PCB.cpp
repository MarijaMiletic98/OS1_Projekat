#include "PCB.h"
#include <dos.h>

PCB::PCB(StackSize sSize, Time tmSlc, Thread* myth):stackSize(sSize/2), timeSlice(tmSlc), myThread(myth), blocked(0), finished(0){ 
    if(stackSize!=0){
        stack=new unsigned[stackSize];
        stack[stackSize-1]=0x200;
        stack[stackSize-2]=FP_SEG(wrapper);
        stack[stackSize-3]=FP_OFF(wrapper);

        ss=FP_SEG(stack+stackSize-12);
        sp=FP_OFF(stack+stackSize-12);

        blockedOnMe=new List();
    }
}

void PCB::wrapper(){
    running->myThread->run();

    lock
    finished=1;
    Thread* t=blockedOnMe->removeFirst();
    while(t){
        t->myPCB->blocked=0;
        Scheduler::put(t);
        t=blockedOnMe->removeFirst();
    }
    unlock
}

PCB::~PCB(){
    delete[] stack;
    delete blockedOnMe;
}