#include"Plane.hpp"
#include<iostream>
using namespace std;

Plane::Plane(int flt, int time, Plane_status status){
    flt_num = flt;
    clock_start = time;
    state = status;
    gas=rand()%5+5;
    cout << "   "<< flt_num <<" 号飞机"<< "准备";
    if (status == arriving)
        cout << "着陆,"; 
    else
        cout << "起飞,";
}

Plane::Plane(){
	gas=0;
    flt_num = -1;
    clock_start = -1;
    state = null;
}

void Plane::wait()const{
    if (state == arriving)
        cout << "进入着陆队列。 " << endl;
    else
        cout << "进入起飞队列。 " << endl;
}

void Plane::wait2()const{
	cout << "进入着陆队列,剩余 "<<gas<<" 单位燃料。" << endl;
}

void Plane::refuse() const{
    if (state == arriving)
		cout << "前往另一个机场着陆。 " << endl;	
    else
        cout << "被告知稍后再尝试起飞。 " << endl;
}

void Plane::land(int time) const{
	int wait = time - clock_start;
    cout << time << ": 飞机编号 " << flt_num << " 在等待 "
        << wait << " 时间单元后着陆机场。 " << endl;
}

void Plane::fly(int time) const{
    int wait = time - clock_start;
    cout << time << ": 飞机编号 " << flt_num << " 在等待 "
        << wait << " 时间单元后从起飞队列起飞。 " << endl;
}

void Plane::fall(int time)const{
    cout << time << ": 飞机编号 " << flt_num << " 因油量不足坠毁。 " << endl;
}

int Plane::started() const{
    return clock_start;
}

int Plane::getgas()const{
	return gas;
}

void Plane::decgas(){
	gas--;
}
