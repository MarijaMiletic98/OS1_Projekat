#include "kernelev.h"

KernelEv::KernelEv(IVTNo ivtNo){
    semaphore=new KernelSem(0);
    if(IVTEntry::IVTable[ivtNo]!=NULL) IVTEntry::IVTable[ivtNo]->event=this;
}

KernelEv::~KernelEv(){
    delete semaphore;
}

void KernelEv::wait(){
    semaphore->wait(0);
}

void KernelEv::signal(){
    if(semaphore->getValue()<0) semaphore->signal();
}