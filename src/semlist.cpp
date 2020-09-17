#include "semlist.h"

SemaphoreList::SemaphoreList():head(NULL),last(NULL){}

void SemaphoreList::add(KernelSem* k){
    lock
    if(!head) {
        head=new Elem(k,NULL);
        last=head;
    }
    else {
        last->next=new Elem(k,NULL);
        last=last->next;
    }
    unlock
}
 
SemaphoreList::~SemaphoreList(){
    lock
    Elem* p=head;
    while(!head){
        head=head->next;
        delete p;
        p=head;
    }
    head=NULL;
    last=NULL;
    unlock
}

void SemaphoreList::checkTime(){
    Elem* p=head;
    while(p){
        int i=p->semaphore->blocked->checkTime();
        p->semaphore->value+=i;
        p=p->next;
    }
}