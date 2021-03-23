#ifndef Extended_queue_hpp
#define Extended_queue_hpp

#include"Queue.hpp"

class Extended_queue: public Queue {
    public:
    	Extended_queue();
    	Extended_queue(int max);
    	~Extended_queue();
        bool full() const;
        int size() const;
        void clear();
        void insert(const Queue_entry &item);
        int go(int time);
        Error_code serve_and_retrieve(Queue_entry &item);
};

#endif
