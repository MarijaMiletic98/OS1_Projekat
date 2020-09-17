#include "kernelsm.h"

SemaphoreList KernelSem::semaphores;

KernelSem::KernelSem(int i):value(i){
    blocked=new List();
    semaphores.add(this);
}

int KernelSem::getValue(){
    return value;
}

int KernelSem::wait (Time maxTimeToWait){
    if(value>0) value--;
    else{
        value--;
        PCB::running->blocked=1;
        Thread* t=PCB::running->myThread;
        blocked->add(t,maxTimeToWait);
        unlock
        dispatch();
        lock
        if(t->myPCB->unblockedAfterTime==1) {
            t->myPCB->unblockedAfterTime=0;
            return 0;
        }
    }
    return 1;
}

int KernelSem::signal(int n){
    if(n==0){
        if(value<0){
            Thread* t=blocked->removeFirst();
            t->myPCB->blocked=0;
            Scheduler::put(t->myPCB);
        } 
        value++;
        return 0;
    }
    if(n>0){
        int x=0;
        if(n>(-value))x=-value;
        else x=n;
        for(int i=0; i<x; i++){
            Thread* t=blocked->removeFirst();
            t->myPCB->blocked=0;
            Scheduler::put(t->myPCB);
        }
        value+=n;
        return x;
    }
    return n;
}

KernelSem::~KernelSem(){
    delete blocked;
}