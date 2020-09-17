#include "thread.h"
#include "System.h"
#include <iostream.h>

class Thread;

class MyThread:public Thread{
public:
    MyThread(int mtr);
    ~MyThread();
protected:
    virtual void run();
private:
    int metersToRun;
};

MyThread::MyThread(int mtr):Thread(), metersToRun(mtr){}

MyThread::~MyThread(){
    waitToComplete();
}

void MyThread::run(){
    while(--metersToRun){
        lock
        cout<<"Niti "<<getId()<<" ostalo je jos "<<metersToRun<<" metara."<<endl;
        unlock
        for(long i=0; i<3000; i++)
            for(long j=0; j<3000; j++);
    }
}

const int N=50;

int userMain(int argc, char** argv){
    int i;
    Thread* threads[N];

    for(i=0; i<N; i++){
        threads[i]=new MyThread(50+i);
        threads[i]->start();
    }

    for(i=0; i<N; i++){
        delete threads[i];
    }

    lock
    cout<<"userMain finished"<<endl;
    unlock

    return 0;
}