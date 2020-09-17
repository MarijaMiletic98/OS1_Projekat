#ifndef _ivtentry_h_
#define _ivtentry_h_

#include "kernelev.h"
#include "thread.h"

#define PREPAREENTRY(ivtNo,oldInterrupt){\
    IVTEntry ivtObj##ivtNo(ivtNo, interruptFunction##ivtNo);\
    void interrupt interruptFunction##ivtNo(...){\
        ivtObj##ivtNo.doSignal();\
        if(oldInterrupt==1) ivtObj##ivtNo.callOldInterrupt();\
        dispatch();\
    }\
}

typedef void interrupt (*IntPointer)(...)

class IVTEntry{
    public:
    IVTEntry(IVTNo iNo, IntPointer i);
    ~IVTEntry();
    void doSignal();
    void callOldInterrupt();

    private:
    friend class KernelEv;
    static IVTEntry* IVTable[256];
    KernelEv* event;
    IntPointer old;
    IVTNo ivtNo;
};
#endif