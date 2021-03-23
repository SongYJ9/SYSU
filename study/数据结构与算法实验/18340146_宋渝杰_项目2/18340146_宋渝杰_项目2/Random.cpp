#include"Random.hpp"
#include<iostream>
using namespace std;

double Random::U_Random()
{
    double f;
    f = (float)(rand()%100);
    return f/100;
}

int Random::poisson(float average){
    int k = 0;
    long double p = 1.0;
    long double l = exp(-average);
    while (p>=l)
    {
        double u = U_Random();
        p *= u;
        k++;
    }
    return k-1;
}

pair<int,int> Random::set(int current_time){
    int land,fly;
    cout << "������ " << current_time << " ʱ��������½�ķɻ������� ";
    cin >> land;
    cout << "������ " << current_time << " ʱ��������ɵķɻ������� ";
    cin >> fly;
    pair<int,int> a(land,fly);
    return a;
}
