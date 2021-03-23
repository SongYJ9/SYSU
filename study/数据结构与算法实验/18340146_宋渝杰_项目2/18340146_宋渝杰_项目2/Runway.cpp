#include"Runway.hpp"
#include<iostream>
using namespace std;

Runway::Runway(int limit):landing(limit),takeoff(limit){
	 queue_limit = limit;
    num_land_requests = num_takeoff_requests = 0;
    num_landings = num_takeoffs = 0;
    num_land_refused = num_takeoff_refused = 0;
    num_land_accepted = num_takeoff_accepted = 0;
    land_wait = takeoff_wait = idle_time = 0;
    num_crash=-1;
}

Runway::Runway(int limit,int max):landing(max),takeoff(limit){
	 queue_limit = limit;
    num_land_requests = num_takeoff_requests = 0;
    num_landings = num_takeoffs = 0;
    num_land_refused = num_takeoff_refused = 0;
    num_land_accepted = num_takeoff_accepted = 0;
    land_wait = takeoff_wait = idle_time = 0;
     num_crash=-1;
}

Error_code Runway::can_land(const Plane &current){
    Error_code result;
    if (landing.size() < queue_limit)
        result = landing.append(current);
    else
        result = fail;
    num_land_requests++;
    if (result != success)
        num_land_refused++;
    else
        num_land_accepted++;
    return result;
}

void Runway::can_land2(const Plane &current){
   landing.insert(current);
   num_land_requests++;
   num_land_accepted++;
}

Error_code Runway::can_depart(const Plane &current){
    Error_code result;
    if (takeoff.size() < queue_limit){
    	result = takeoff.append(current);
    }else{
    	result = fail;
    }
    
    num_takeoff_requests++;
    if (result != success)
        num_takeoff_refused++;
    else
        num_takeoff_accepted++;
    return result;
}
// P1��P6 
Runway_activity Runway::activity1(int time, Plane &moving){
    Runway_activity in_progress;
    if (!landing.empty()) {
        landing.retrieve(moving);
        land_wait += time - moving.started();
        num_landings++;
        in_progress = land;
        landing.serve();
    }else if (!takeoff.empty()) {
        takeoff.retrieve(moving);
        takeoff_wait += time - moving.started();
        num_takeoffs++;
        in_progress = takeof;
        takeoff.serve();
    }else {
        idle_time++;
        in_progress = idle;
    }
    return in_progress;
}

// P2
Runway_activity Runway::activity2(int time, Plane &moving, Plane &moving2){
    Runway_activity in_progress;
    if(!landing.empty() and !takeoff.empty()){
        landing.retrieve(moving);
        land_wait += time - moving.started();
        num_landings++;
        landing.serve();
        takeoff.retrieve(moving2);
        takeoff_wait += time - moving2.started();
        num_takeoffs++;
        in_progress = land_and_takeof;
        takeoff.serve();
    }else if (!landing.empty()) {
        landing.retrieve(moving);
        land_wait += time - moving.started();
        num_landings++;
        in_progress = land;
        landing.serve();
    }else if (!takeoff.empty()) {
        takeoff.retrieve(moving2);
        takeoff_wait += time - moving2.started();
        num_takeoffs++;
        in_progress = takeof;
        takeoff.serve();
    }else {
        idle_time++;
        in_progress = idle;
    }
    return in_progress;
}

// P3
Runway_activity Runway::activity3(int time, Plane &moving, Plane &moving2){
    Runway_activity in_progress;
    if(!landing.empty() and !takeoff.empty()){
        landing.retrieve(moving);
        land_wait += time - moving.started();
        num_landings++;
        landing.serve();
        takeoff.retrieve(moving2);
        takeoff_wait += time - moving2.started();
        num_takeoffs++;
        in_progress = land_and_takeof;
        takeoff.serve();
    }else if (!landing.empty()) {
        if(landing.size() > 1){
            landing.retrieve(moving);
            land_wait += time - moving.started();
            num_landings++;
            landing.serve();
            landing.retrieve(moving2);
            land_wait += time - moving2.started();
            num_landings++;
            landing.serve();
            in_progress = land2;
        }else{
            landing.retrieve(moving);
            land_wait += time - moving.started();
            num_landings++;
            in_progress = land;
            landing.serve();
        }
    }else if (!takeoff.empty()) {
        if(takeoff.size() > 1){
            takeoff.retrieve(moving2);
            takeoff_wait += time - moving2.started();
            num_takeoffs++;
            takeoff.serve();
            takeoff.retrieve(moving);
            takeoff_wait += time - moving.started();
            num_takeoffs++;
            in_progress = takeof2;
            takeoff.serve();
        }else{
            takeoff.retrieve(moving2);
            takeoff_wait += time - moving2.started();
            num_takeoffs++;
            in_progress = takeof;
            takeoff.serve();
        }
    }else {
        idle_time++;
        in_progress = idle;
    }
    return in_progress;
}

// P4
Runway_activity Runway::activity4(int time, Plane &moving, Plane &moving2, Plane &moving3){
    Runway_activity in_progress;
    if(!landing.empty() and !takeoff.empty()){
        if(landing.size() > 1){
            landing.retrieve(moving);
            land_wait += time - moving.started();
            num_landings++;
            landing.serve();
            landing.retrieve(moving2);
            land_wait += time - moving2.started();
            num_landings++;
            landing.serve();
            takeoff.retrieve(moving3);
            takeoff_wait += time - moving3.started();
            num_takeoffs++;
            in_progress = land2_and_takeof;
            takeoff.serve();
        }else if(takeoff.size() > 1){
            landing.retrieve(moving);
            land_wait += time - moving.started();
            num_landings++;
            landing.serve();
            takeoff.retrieve(moving2);
            takeoff_wait += time - moving2.started();
            num_takeoffs++;
            takeoff.serve();
            takeoff.retrieve(moving3);
            takeoff_wait += time - moving3.started();
            num_takeoffs++;
            takeoff.serve();
            in_progress = land_and_takeof2;
        }else{
            landing.retrieve(moving);
            land_wait += time - moving.started();
            num_landings++;
            landing.serve();
            takeoff.retrieve(moving2);
            takeoff_wait += time - moving2.started();
            num_takeoffs++;
            in_progress = land_and_takeof;
            takeoff.serve();
        }
    }else if (!landing.empty()) {
        if(landing.size() > 1){
            landing.retrieve(moving);
            land_wait += time - moving.started();
            num_landings++;
            landing.serve();
            landing.retrieve(moving2);
            land_wait += time - moving2.started();
            num_landings++;
            landing.serve();
            in_progress = land2;
        }else{
            landing.retrieve(moving);
            land_wait += time - moving.started();
            num_landings++;
            in_progress = land;
            landing.serve();
        }
    }else if (!takeoff.empty()) {
        if(takeoff.size() > 1){
            takeoff.retrieve(moving2);
            takeoff_wait += time - moving2.started();
            num_takeoffs++;
            takeoff.serve();
            takeoff.retrieve(moving);
            takeoff_wait += time - moving.started();
            num_takeoffs++;
            in_progress = takeof2;
            takeoff.serve();
        }else{
            takeoff.retrieve(moving2);
            takeoff_wait += time - moving2.started();
            num_takeoffs++;
            in_progress = takeof;
            takeoff.serve();
        }
    }else {
        idle_time++;
        in_progress = idle;
    }
    return in_progress;
}

// P5 
Runway_activity Runway::activity5(int time, Plane &moving){
	Runway_activity in_progress;
	if( num_crash==-1) num_crash=0;
	 num_crash +=landing.go(time);
    if (!landing.empty()) {
        landing.retrieve(moving);
        land_wait += time - moving.started();
        num_landings++;
        in_progress = land;
        landing.serve();
    }else if (!takeoff.empty()) {
        takeoff.retrieve(moving);
        takeoff_wait += time - moving.started();
        num_takeoffs++;
        takeoff.serve();
        in_progress = takeof;
    }else {
        idle_time++;
        in_progress = idle;
    }
    return in_progress;
	
}

void Runway::shut_down(int time) const{
	cout<< "\nģ���� " << time << " ʱ�������� " << endl
	    << "  ����ķɻ������� "<< (num_land_requests + num_takeoff_requests) << endl
	    << "  Ҫ����½�ķɻ������� "<< num_land_requests << endl
	    << "  Ҫ����ɵķɻ������� "<< num_takeoff_requests << endl
	    << "  ������½�ķɻ������� "<< num_land_accepted << endl
	    << "  ������ɵķɻ������� "<< num_takeoff_accepted << endl;
	if(num_crash==-1) cout<< "  �ܾ���½�ķɻ������� "<< num_land_refused << endl;
	else cout<<"  ׹�ٵķɻ������� "<<num_crash<<endl; 
	cout<< "  �ܾ���ɵķɻ������� "<< num_takeoff_refused << endl
	    << "  ��½�ķɻ������� "<< num_landings << endl
	    << "  ��ɵķɻ������� "<< num_takeoffs << endl;
	cout<< "  ������½������ķɻ������� "<< landing.size() << endl
	    << "  ������ɶ�����ķɻ������� "<< takeoff.size() << endl; 
	cout<< "  �ɻ��ܵ����е�ʱ��ٷֱȣ� "<< 100.0 * ((float) idle_time)/((float) time) << "%" << endl;
	if(num_landings>0)	cout << "  �ɻ���½��ƽ���ȴ�ʱ���� "<< ((float) land_wait)/((float) num_landings) << endl;
	else	cout<<"  �޷ɻ���½"<<endl; 
	if(num_takeoffs>0) 	cout << "  �ɻ���ɵ�ƽ���ȴ�ʱ���� "<< ((float) takeoff_wait)/((float) num_takeoffs) << endl;
	else	cout<<"  �޷ɻ����"<<endl;
	cout << "  ϣ����½�ķɻ�ƽ�����۲���Ϊ�� ÿ��λʱ�� "<< ((float) num_land_requests)/((float) time) << " �ܡ� " << endl;
	cout << "  ϣ����ɵķɻ�ƽ�����۲���Ϊ�� ÿ��λʱ�� "<< ((float) num_takeoff_requests)/((float) time) << " �ܡ� " << endl;
}
