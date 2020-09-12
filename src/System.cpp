#include "System.h"
#include "PCB.h"

class PCB;

volatile int System::context_switch_on_demand=0;
volatile int System::cntr=1;
volatile int System::lockFlag=0;
Thread* System::main=NULL;
Thread* System::loopth=NULL;
pInterrupt System::oldInterr=NULL;

void System::startSystem(){
    main=new Thread(0,1);
    PCB::running=main->myPCB;
    oldInterr=getvect(8);
    setvect(8,timerInterrupt);
    loopth=new LoopThread(100,1);
    loopth->start();
}

void System::endSystem(){
    setvect(8,oldInterr);
    delete main;
    delete loopth;
}

volatile int flag;
volatile unsigned tsp, tss, tbp;

void interrupt System::timerInterrupt(...){
    asm cli;
    flag=0;
    if(context_switch_on_demand) flag=1;
    else{
        oldInterr();
        // tick(); //otkomentarisati kasnije
        if(cntr!=0) {
            cntr--;
            if(cntr==0) flag=1;
        }
        KernelSem::semaphores.checkTime();
    }
    if(flag){
        if(!lockFlag){
            asm{
                mov tsp, sp
                mov tss, ss
                mov tbp, bp
            }
            PCB::running->sp=tsp;
            PCB::running->ss=tss;
            PCB::running->bp=tbp;

            if(PCB::running->blocked==0) Scheduler::put((PCB*)PCB::running);
            PCB::running=Scheduler::get();

            if(PCB::running==NULL) PCB::running=loopth->myPCB;

            tsp=PCB::running->sp;
            tss=PCB::running->ss;
            tbp=PCB::running->bp;

            asm{
                mov sp, tsp
                mov ss, tss
                mov bp, tbp
            } 

            cntr=PCB::running->timeSlice;
            context_switch_on_demand=0;
        }else{
            context_switch_on_demand=1;
        }
    }
}