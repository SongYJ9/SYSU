#ifndef Runway_hpp
#define Runway_hpp

#include"Extended_queue.hpp"

enum Runway_activity {idle, land, land2, takeof, takeof2, land_and_takeof, land2_and_takeof, land_and_takeof2};
class Runway {
    public:
        Runway(int limit);
        Runway(int limit,int max);
        Error_code can_land(const Plane &current);
        void can_land2(const Plane &current);
        Error_code can_depart(const Plane &current);
        Runway_activity activity1(int time, Plane &moving);// P1°¢P6Õ®”√ 
        Runway_activity activity2(int time, Plane &moving, Plane &moving2);
        Runway_activity activity3(int time, Plane &moving, Plane &moving2);
        Runway_activity activity4(int time, Plane &moving, Plane &moving2, Plane &moving3);
		Runway_activity activity5(int time, Plane &moving);
        void shut_down(int time) const;
    private:
        Extended_queue landing;
        Extended_queue takeoff;
        
        int queue_limit;
        int num_land_requests;
        int num_takeoff_requests;
        int num_landings;
        int num_takeoffs;
        int num_crash;
        int num_land_accepted;
        int num_takeoff_accepted;
        int num_land_refused;
        int num_takeoff_refused;
        int land_wait;
        int takeoff_wait;
        int idle_time;
};

#endif 
