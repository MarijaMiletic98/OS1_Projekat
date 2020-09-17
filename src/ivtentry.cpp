#include "ivtentry.h"

IVTEntry::IVTEntry(IVTNo iNo, IntPointer i):ivtNo(iNo){
    IVTable[ivtNo]=this;
    old=getvect(ivtNo);
    setvect(ivtNo,i);
}

void IVTEntry::doSignal(){
    lock
    if(event) event->signal();
    unlock
}

IVTEntry::~IVTEntry(){
    IVTable[ivtNo]=NULL;
    setvect(ivtNo, old);
}

void IVTEntry::callOldInterrupt(){
    old();
}