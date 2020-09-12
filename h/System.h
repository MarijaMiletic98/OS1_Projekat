#ifndef _system_h_
#define _system_h_

#include "thread.h"
#include "PCB.h"
#include <dos.h>
#include <iostream.h>
#include "kernelsm.h"

#define lock System::lockFlag++;
#define unlock {System::lockFlag--; if(System::lockFlag && System::context_switch_on_demand) dispatch();}

typedef void interrupt (*pInterrupt)(...);

class Thread;
class PCB;

class System{
    public:
    static void startSystem();
    static void endSystem();
    static void interrupt timerInterrupt(...);
    static volatile int lockFlag;
    static volatile int context_switch_on_demand;

    private:
    friend void dispatch();
    friend class Thread;
    static Thread* main;
    static pInterrupt oldInterr;
    static volatile int cntr;
    static Thread* loopth;
};
#endif