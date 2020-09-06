#include "thread.h"

Thread::Thread(StackSize stackSize=defaultStackSize,Time timeSlice=defaultTimeSlice){
    id=posID++;
    if(stackSize>=64536)stackSize=64536;
    myPCB=new PCB(stackSize, timeSlice, this);
    list.add(this);
}

ID Thread::getId(){
    return id;
}

static ID Thread::getRunningId(){
    return running->myThread->id;
}

static Thread* Thread::getThreadById(ID id){
    return list.get(id);
}

virtual Thread::~Thread(){
    waitToComplete();
    delete myPCB;
    list.remove(id);
}

void start(){
    lock
    Scheduler::put(myPCB);
    unlock
}

void waitToComplete(){
    if(this==running->myThread) return;
    if(this==System::main) return;
    if(this==System::loopth) return;
    if(this->myPCB->finished) return;
    myPCB->blockedOnMe.add(running->myThread);
    myPCB->blocked=1;
    dispatch();
}

ID Thread::posID=0;
List Thread::list;

void dispatch(){
    System::context_switch_on_demand=1;
    System::timerInterrupt();
}