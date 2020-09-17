#include "thread.h"
#include "semaphor.h"
#include "System.h"
#include <iostream.h>
#include <dos.h>

class Thread;

int mutex_glb = 1;

void mutex_glb_wait(){
	sloop:asm{
		mov ax, 0
		xchg ax, mutex_glb 	
	}
	if(_AX ==0){
		dispatch();
		asm jmp sloop;
	}
}

#define print(X) {mutex_glb_wait(); cout<<X<<endl; mutex_glb=1;}

const int BUFFER_SIZE = 20;

class BoundedBuffer {
public:
   BoundedBuffer ();
   void append (char);
   void appendChunk(char*, int);
   char take ();
   int  size() {return itemAvailable.val();}; 
private:
   Semaphore mutex;
   Semaphore spaceAvailable, itemAvailable;
   char buffer[BUFFER_SIZE];
   int head, tail;
};

BoundedBuffer::BoundedBuffer () : mutex(1), spaceAvailable(BUFFER_SIZE), itemAvailable(0),
   head(0), tail(0) {}

void BoundedBuffer::append (char d) {
   spaceAvailable.wait(0);
   mutex.wait(0);
   buffer[tail] = d;
   tail = (tail+1)%BUFFER_SIZE;
   mutex.signal(0);
   itemAvailable.signal(0);
}

void BoundedBuffer::appendChunk(char* chunk, int size){
   for(int i=0;i<size;i++){
      spaceAvailable.wait(0);
      mutex.wait(0);
      buffer[tail] = chunk[i];
      tail = (tail+1)%BUFFER_SIZE;
      mutex.signal(0);
   }
   itemAvailable.signal(size);
}

char BoundedBuffer::take () {
   itemAvailable.wait(0);
   mutex.wait(0);
   char d = buffer[head];
   head = (head+1)%BUFFER_SIZE;
   mutex.signal(0);
   spaceAvailable.signal(0);
   return d;
}

void outputDelay() {
   delay(20);
};

class Producer : public Thread {
public:
   Producer(BoundedBuffer* bb,char y):myBuffer(bb),x(y) {}
   virtual ~Producer(){waitToComplete();}
protected:
   virtual void run ();
   char produce();
   BoundedBuffer* myBuffer;
   char x;
};

char Producer::produce() {
   return x;
}; // Produce an item

void Producer::run () {
   while(1) {
      outputDelay();
      char d = produce();
      myBuffer->append(d);
      print("proizveo "<<x<<" u baferu ima "<<myBuffer->size()<<" elemenata");
   }
}

class MassProducer : public Producer{
public:
   MassProducer(BoundedBuffer* bb,char y):Producer(bb,y){}
   virtual ~MassProducer(){waitToComplete();}
protected:
   virtual void run();
};

void MassProducer::run(){
   while(1){
      outputDelay();
      char d[10];
      for(int i=0;i<10;i++) d[i] = produce();
      myBuffer->appendChunk(d, 10);
      print("proizveo 10 "<<x<<" u baferu ima "<<myBuffer->size()<<" elemenata");
   }
}

class Consumer : public Thread {
public:
   Consumer (BoundedBuffer* bb) : myBuffer(bb) {}
   virtual ~Consumer(){waitToComplete();}
protected:
   virtual void run ();
   void consume(char p);
private:
   BoundedBuffer* myBuffer;
};

void Consumer::consume(char p){print(p);} // Consume an item

void Consumer::run () {
   while(1) {
      outputDelay();
      char d = myBuffer->take();
      consume(d);
   }
  
   while (myBuffer->size()){
      outputDelay();
      char d = myBuffer->take();
      consume(d);
   }
   print("\nKraj PRODUCER-BUFFER-CONSUMER!");
}

class PrintingThread : public Thread {
public:
	PrintingThread(char *nm, StackSize sts = defaultStackSize, Time tslc = defaultTimeSlice) : Thread(sts, tslc), name(nm) {};
   virtual ~PrintingThread(){waitToComplete();}
protected:
	virtual void run();	
private:
	char *name;
};

void PrintingThread::run() {
	long i,j;
	for (i=0;i<300;i++) {
		print(name << " : rUnNiNg!");
      outputDelay();
	}
}

class MinimalThread : public Thread {
public:
	MinimalThread() : Thread(defaultStackSize, 1), number(0) {};
   virtual ~MinimalThread(){waitToComplete();}
	void setNumber(int n) {number = n;};
protected:
	virtual void run();
private:
	int number;
};

void MinimalThread::run() {
	print("MinimalThread - " << number << ":eNdInG!");
}

const int N = 50;

int userMain(int argc, char* argv[]) {
   long i,j;

   BoundedBuffer buff;
   Consumer con(&buff);
   Producer * pro[N+1];

   for (i=0; i<N; i++){
      pro[i] = new Producer(&buff, '0'+i);
      pro[i]->start();
   } 
   pro[N] = new MassProducer(&buff, '0'+3);
   pro[N]->start();
   con.start();

   PrintingThread t1("Thread 1", defaultStackSize, 1),t2("Thread 2", defaultStackSize, 3),t3("Thread 3", defaultStackSize, 2);								 
	t1.start();
	t2.start();
	t3.start();
	
	MinimalThread threads[20];
	for (i=0;i<20;i++) threads[i].setNumber(i);
	for (i=0;i<20;i++) threads[i].start();

   for(i=1;i<=20;i++) {
      print("userMain(" << i << ")");
      delay(3);
   }

   for(i=0;i<N+1;i++){
      delete pro[i];
   }

   return 0;
}
