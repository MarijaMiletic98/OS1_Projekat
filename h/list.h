#ifndef _list_h_
#define _list_h_

#include "thread.h"
#include <stdlib.h>

class Thread;
typedef int ID;

class List{
    public:
    List();
    void add(Thread* t, int blockedWaitingTime=0);
    Thread* remove(ID id);
    Thread* get(ID id);
    Thread* removeFirst();
    int checkTime();
    virtual ~List();

    private:
    struct Elem{
        Thread* thread;
        int blockedWaitingTime;
        Elem* next;
        Elem(Thread* t, Elem* n, int b=0):thread(t), next(n), blockedWaitingTime(b){}
    };
    Elem* head, *last;
};
#endif