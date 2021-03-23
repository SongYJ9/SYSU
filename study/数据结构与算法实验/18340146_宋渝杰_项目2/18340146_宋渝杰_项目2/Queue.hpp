#ifndef Queue_hpp
#define Queue_hpp

#include"Plane.hpp"
typedef Plane Queue_entry;

enum Error_code{ success, fail, underflow, overflow};
class Queue {
    public:
        Queue();
        Queue(int max);
        ~Queue();
        bool empty() const;
        Error_code serve();
        Error_code append(const Queue_entry &item);
        Error_code retrieve(Queue_entry &item) const;
    protected:
        int count;
        int front, rear;
        int maxqueue;
        Queue_entry* entry;
};

#endif 
