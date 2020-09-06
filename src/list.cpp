#include "list.h"

List::List():head(NULL),last(NULL){}

void List::add(Thread* t){
    lock
    if(!head) {
        head=new Elem(t,NULL);
        last=head;
    }
    else {
        last->next=new Elem(t,NULL);
        last=last->next;
    }
    unlock
}

Thread* List::remove(ID id){
    lock
    Elem* p=head, *preth=NULL;
    while(p){
        if(p->thread->getID()==id) {
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
        if(p->thread->getID()==id) {
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