#include"Extended_queue.hpp"
#include<iostream>
using namespace std;

Extended_queue::Extended_queue():Queue(){}

Extended_queue::Extended_queue(int max):Queue(max){}

Extended_queue::~Extended_queue(){}

bool Extended_queue::full() const{
    return count == maxqueue;
}

int Extended_queue::size() const{
    return count;
}

void Extended_queue::clear(){
    count = 0;
    rear = maxqueue - 1;
    front = 0;
}

void Extended_queue::insert(const Queue_entry &item){
    if(count==0 or item.getgas()>=entry[rear].getgas()){
    	append(item);
    }else{
    	for(int i=0;i<count;i++){
    		if(item.getgas()<entry[(i+front)%maxqueue].getgas()){
    			for(int j=rear+1;j!=(i+front)%maxqueue;j--){
    				entry[j%maxqueue]=entry[(j+maxqueue-1)%maxqueue];
    			}
    			count++;
   				 rear = ((rear + 1) == maxqueue) ? 0 : (rear + 1);
    			entry[(i+front)%maxqueue]=item;
    			break;
    		}
    		
   		}
    }
}

int Extended_queue::go(int time){
	Queue_entry item;
	int num=0;
	while(!empty()){
		if(entry[front].getgas()<=0){
			entry[front].fall(time);
			serve();
			num++;
		}else break;
	}
	for(int i=0;i<count;i++) entry[(i+front)%maxqueue].decgas();
	return num;
}

Error_code Extended_queue::serve_and_retrieve(Queue_entry &item){
    if (count <= 0) return underflow;
    else{
        item = entry[front];
        count--;
        front = ((front + 1) == maxqueue) ? 0 : (front + 1);
        return success;
    }
}
