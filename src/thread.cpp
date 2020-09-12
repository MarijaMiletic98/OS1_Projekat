#include "thread.h"

Thread::Thread(StackSize stackSize,Time timeSlice){
    id=posID++;
    if(stackSize>=65536)stackSize=65536;
    myPCB=new PCB(stackSize, timeSlice, this);
    list.add(this);
}

ID Thread::getId(){
    return id;
}

ID Thread::getRunningId(){
    return PCB::running->myThread->id;
}

Thread* Thread::getThreadById(ID id){
    return list.get(id);
}

Thread::~Thread(){
    waitToComplete();
    delete myPCB;
    list.remove(id);
}

void Thread::start(){
    lock
    Scheduler::put(myPCB);
    unlock
}

void Thread::waitToComplete(){
    lock
    if(this==PCB::running->myThread) return;
    if(this==System::main) return;
    if(this==System::loopth) return;
    if(this->myPCB->finished) return;
    myPCB->blockedOnMe->add(PCB::running->myThread);
    PCB::running->blocked=1;
    unlock
    dispatch();
}

ID Thread::posID=0;
List Thread::list;

void LoopThread::run(){
    while(1);
}

void dispatch(){
    System::context_switch_on_demand=1;
    System::timerInterrupt();
}