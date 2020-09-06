#ifndef _list_h_
#define _list_h_

class List{
    public:
    List();
    void add(Thread* t);
    Thread* remove(ID id);
    Thread* get(ID id);
    Thread* removeFirst();
    virtual ~List();

    private:
    struct Elem{
        Thread* thread;
        Elem* next;
        Elem(Thread* t, Elem* n):thread(t), next(n){}
    }
    Elem* head, *last;
};
#endif