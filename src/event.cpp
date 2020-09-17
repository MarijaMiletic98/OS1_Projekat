#include "event.h"

Event::Event (IVTNo ivtNo){
    parent=PCB::running;
    myImpl=new KernelEv(ivtNo);
}

Event::~Event (){
    delete myImpl;
}

void wait (){
    if(parent==PCB::running){
        lock
        myImpl->wait();
        unlock
    }
}

void signal(){
    lock
    myImpl->signal();
    unlock
}