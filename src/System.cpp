#include "System.h"

int System::context_switch_on_demand=0;
int System::cntr=1;
int System::lockFlag=0;

void System::startSystem(){
    main=new Thread(0,1);
    running=main->myPCB;
    oldInterr=getvect(8);
    setvect(8,timerInterrupt);
    loopth=new LoopThread(100,1);
    loopth->start();
}

void System::endSystem(){
    lock
    delete main;
    delete loopth;
    setvect(8,oldInterr);
    unlock
}

volatile int flag;
volatile unsigned tsp, tss;

void interrupt System::timerInterrupt(...){
    asm cli;
    flag=0;
    if(context_switch_on_demand) flag=1;
    else{
        oldInterr();
        tick();
        if(cntr!=0) {
            cntr--;
            if(cntr==0) flag=1;
        }
    }
    if(flag){
        if(!lockFlag){
            asm{
                mov tsp, sp
                mov tss, ss
            }
            running->sp=tsp;
            running->ss=tss;

            if(running->blocked==0) Scheduler::put(running);
            running=Scheduler::get();

            if(running==NULL) running=loopth;

            tsp=running->sp;
            tss=running->ss;

            asm{
                mov sp, tsp
                mov ss, tss
            } 

            cntr=running->timeSlice;
            context_switch_on_demand=0;
        }else{
            context_switch_on_demand=1;
        }
    }
}