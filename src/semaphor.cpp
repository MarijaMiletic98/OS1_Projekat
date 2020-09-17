#include "semaphor.h"

Semaphore::Semaphore (int init){
    myImpl=new KernelSem(init);
}

Semaphore::~Semaphore (){
    delete myImpl;
}

int Semaphore::wait (Time maxTimeToWait){
    lock
    int x=myImpl->wait(maxTimeToWait);
    unlock
    return x;
}

int Semaphore::signal(int n){
    lock
    int x=myImpl->signal(n);
    unlock
    return x;
}

int Semaphore::val () const{
    return myImpl->getValue();
}