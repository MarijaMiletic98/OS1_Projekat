#ifndef _system_h_
#define _system_h_

#define lock lockFlag=1;
#define unlock {lockFlag=0; if(context_switch_on_demand) dispatch();}

typedef void interrupt (*pInterrupt)(...);

class System{
    public:
    static void startSystem();
    static void endSystem();
    static void interrupt timerInterrupt(...);

    private:
    friend void dispatch();
    static volatile int context_switch_on_demand;
    static Thread* main;
    static pInterrupt oldInterr;
    static volatile int cntr;
    static Thread* loopth;
    static volatile int lockFlag;
};
#endif