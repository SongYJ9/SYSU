#ifndef Random_hpp
#define Random_hpp

#include <cmath>
#include <ctime>
#include <cstdlib>
#include <utility> 
using namespace std;

class Random{
    public:
        Random(){}
        int poisson(float average);
        double U_Random();
        pair<int,int> set(int current_time);
};

#endif 
