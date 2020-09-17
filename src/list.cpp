#include "list.h"

List::List():head(NULL),last(NULL){}

void List::add(Thread* t, int blockedWaitingTime){
    lock
    if(!head) {
        head=new Elem(t,NULL,blockedWaitingTime);
        last=head;
    }
    else {
        last->next=new Elem(t,NULL, blockedWaitingTime);
        last=last->next;
    }
    unlock
}

Thread* List::remove(ID id){
    lock
    Elem* p=head, *preth=NULL;
    while(p){
        if(p->thread->getId()==id) {
            Thread* t=p->thread;
            if(preth) preth->next=p->next;
            else {
                head=head->next;
                if(!head) last=NULL;
            }
            if(!p->next)last=preth;
            delete p;
            unlock
            return t;
        }
        preth=p;
        p=p->next;
    }    
    unlock    
    return NULL;
}

Thread* List::get(ID id){
    lock
    Elem* p=head;
    while(p){
        if(p->thread->getId()==id) {
            unlock
            return p->thread;
        }
        p=p->next;
    }   
    unlock     
    return NULL;
}

Thread* List::removeFirst(){
    lock
    Elem* p=head;
    if(head==NULL) {
        unlock
        return NULL;
    }
    head=head->next;
    if(head==NULL) last=NULL;
    Thread* th=p->thread;
    delete p;
    unlock
    return th;
}

int List::checkTime(){
    int i=0;
    Elem* p=head, *preth=NULL;
    while(p){
        if(p->blockedWaitingTime>0) {
            p->blockedWaitingTime--;
            if(p->blockedWaitingTime==0){
                Thread* t=p->thread;
                if(preth==NULL){
                    head=head->next;
                    if(head==NULL) last=NULL;
                }
                else preth->next=p->next;
                delete p;
                if(preth) p=preth->next;
                else p=head;
                t->myPCB->blocked=0;
                t->myPCB->unblockedAfterTime=1;
                Scheduler::put(t->myPCB);
                i++;
            }else{
                preth=p;
                p=p->next;
            }
        }
        else{
            preth=p;
            p=p->next;
        }
    }
    return i;
}
    
List::~List(){
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