#ifndef _kernelev_h_
#define _kernelev_h_

#include "event.h"
#include "kernelsm.h"

class KernelEv{
    public:
    KernelEv(IVTNo ivtNo);
    ~KernelEv();
    void wait();
    void signal();

    private:
    KernelSem* semaphore;
};
#endif