#include"Plane.hpp"
#include<iostream>
using namespace std;

Plane::Plane(int flt, int time, Plane_status status){
    flt_num = flt;
    clock_start = time;
    state = status;
    gas=rand()%5+5;
    cout << "   "<< flt_num <<" �ŷɻ�"<< "׼��";
    if (status == arriving)
        cout << "��½,"; 
    else
        cout << "���,";
}

Plane::Plane(){
	gas=0;
    flt_num = -1;
    clock_start = -1;
    state = null;
}

void Plane::wait()const{
    if (state == arriving)
        cout << "������½���С� " << endl;
    else
        cout << "������ɶ��С� " << endl;
}

void Plane::wait2()const{
	cout << "������½����,ʣ�� "<<gas<<" ��λȼ�ϡ�" << endl;
}

void Plane::refuse() const{
    if (state == arriving)
		cout << "ǰ����һ��������½�� " << endl;	
    else
        cout << "����֪�Ժ��ٳ�����ɡ� " << endl;
}

void Plane::land(int time) const{
	int wait = time - clock_start;
    cout << time << ": �ɻ���� " << flt_num << " �ڵȴ� "
        << wait << " ʱ�䵥Ԫ����½������ " << endl;
}

void Plane::fly(int time) const{
    int wait = time - clock_start;
    cout << time << ": �ɻ���� " << flt_num << " �ڵȴ� "
        << wait << " ʱ�䵥Ԫ�����ɶ�����ɡ� " << endl;
}

void Plane::fall(int time)const{
    cout << time << ": �ɻ���� " << flt_num << " ����������׹�١� " << endl;
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
