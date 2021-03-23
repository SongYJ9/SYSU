#include"Queue.hpp"
#include<iostream>
using namespace std;

Queue::Queue(){  
	maxqueue = 0;
    count = 0;
    rear = maxqueue - 1;
    front = 0;
    entry = NULL;
}

Queue::Queue(int max){
	maxqueue = max;
    count = 0;
    front = 0;
    rear = maxqueue-1;
    entry = new Queue_entry[maxqueue];
}

Queue::~Queue(){
	if(entry!=NULL) delete []entry;
}

bool Queue::empty() const{
    return count == 0;
}

//尾部增加元素 
Error_code Queue::append(const Queue_entry &item){
    if (count >= maxqueue) return overflow;
    count++;
    rear = ((rear + 1) == maxqueue) ? 0 : (rear + 1);
    entry[rear] = item;
    return success;
}

// 删除头部元素 
Error_code Queue::serve(){
    if (count <= 0) return underflow;
    count--;
    front = ((front + 1) == maxqueue) ? 0 : (front + 1);
    return success;
}

//获取头部元素 
Error_code Queue::retrieve(Queue_entry &item) const{
    if (count <= 0) return underflow;
    item = entry[front];
    return success;
}
