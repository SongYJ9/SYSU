#ifndef Plane_hpp
#define Plane_hpp

#include <cstdlib> 
using namespace std; 

enum Plane_status {null, arriving, departing};
class Plane {
    public:
        Plane();
        Plane(int flt, int time, Plane_status status);
        void refuse() const;
        void wait()const;
        void land(int time) const;
        void fly(int time) const;
        void fall(int time)const;
        int started() const;
        int getgas()const;
        void decgas();
        void wait2()const;
    private:
        int flt_num;
        int clock_start;
        int gas; 
        Plane_status state;
};

#endif 
