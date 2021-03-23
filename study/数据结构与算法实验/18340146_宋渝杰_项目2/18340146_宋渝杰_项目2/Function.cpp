#include<iostream>
#include<cmath>
#include<string>
#include<conio.h>
#include<windows.h> 

#include"Function.hpp"
#include"Plane.hpp"
#include"Runway.hpp"
#include"Random.hpp"
using namespace std;

void initialize(int &end_time, int &queue_limit,double &arrival_rate, double &departure_rate,int flag){ //P1-P5的输入函数 
    if(flag) cout << "-在任意的时间等待着陆或者起飞的飞机数的最大数目是多少？ "<< flush;
    else cout << "-在任意的时间等待起飞的飞机数的最大数目是多少？ "<< flush;
   	CI1:
	fflush(stdin);
    cin >> queue_limit;
    if(!cin.good() or queue_limit<=0){
    	cin.clear(); cin.sync();
    	cerr << "--输入错误,请重新输入: ";
		goto CI1;
    }
      
    cout << "-模拟多长的时间？ " << flush;
    CI2:
    fflush(stdin);
	cin >> end_time;
    if(!cin.good() or end_time<=0){
    	cin.clear(); cin.sync();
    	cerr << "--输入错误,请重新输入: ";
		goto CI2;
    }
    
    cout << "-平均一个时间有多少架飞机降落？ " << flush;
    CI3:
    fflush(stdin);
	cin >> arrival_rate;
    if(!cin.good() or arrival_rate<=0){
    	cin.clear(); cin.sync();
    	cerr << "--输入错误,请重新输入: ";
		goto CI3;
    }
    cout << "-平均一个时间有多少架飞机起飞？ " << flush;
    CI4:
    fflush(stdin);
	cin >> departure_rate;
    if(!cin.good() or departure_rate<=0){
    	cin.clear(); cin.sync();
    	cerr << "--输入错误,请重新输入: ";
		goto CI4;
    }
        
  
}

void initialize(int &end_time, int &queue_limit){ //P6输入函数 
    
    cout << "-在任意的时间等待着陆或者起飞的飞机数的最大数目是多少？ "<< flush;
    CL1:
    fflush(stdin);
	cin >> queue_limit;
	if(!cin.good() or queue_limit<=0){
    	cin.clear(); cin.sync();
    	cerr << "--输入错误,请重新输入: ";
		goto CL1;
    }
    cout << "-模拟多长的时间？ " << flush;
    CL2: 
	fflush(stdin);
    cin >> end_time;
    if(!cin.good() or end_time<=0){
    	cin.clear(); cin.sync();
    	cerr << "--输入错误,请重新输入: ";
		goto CL2;
    }
}

void run_idle(int time){
    cout << time << ": 跑道是闲置的。 " << endl;
}

void Menu(){ //菜单显示 
	Base_Print();
	cout<<"\n\t\t\t\t\t\t    起 始 页"; 
	cout<<"\n\n\n";
	cout<<"\t\t\t\t\t(1) 方案一";	
	cout<<"\t\t(2) 方案二\n\n";	
	cout<<"\t\t\t\t\t(3) 方案三";	
	cout<<"\t\t(4) 方案四\n\n";
	cout<<"\t\t\t\t\t(5) 方案五";	
	cout<<"\t\t(6) 方案六\n\n";
	cout<<"\t\t\t\t\t(q) 结束程序\n";			
	cout<<"\n\t\t\t\t请输入指令(输入序号):";			
}

void Base_Print(){
	cout<<"\n";
	cout<<"\t\t\t\t\t  ----------------------------"<<endl;
	cout<<"\t\t\t\t\t  |机  ※  场  ※  调  ※  度|"<<endl;
	cout<<"\t\t\t\t\t  ----------------------------"<<endl;
}

void Subpro1(){ //P1 
	int end_time;
    int queue_limit;
    int flight_number = 1; 
    double arrival_rate, departure_rate;
    Random variable;
    
	cout << "这个机场只有一条跑道用于着陆和起飞。" << endl
    	<< "在一个时间内只有一架飞机可以着陆或者起飞。" << endl<< endl;;
    srand((unsigned)time(NULL));
	initialize(end_time, queue_limit, arrival_rate, departure_rate,true);
    Runway small_airport(queue_limit);
	
	for (int current_time = 0; current_time < end_time; current_time++) {
//        飞机降落
        int number_arrivals = variable.poisson(arrival_rate);
        for (int i = 0; i < number_arrivals; i++) {
            Plane current_plane(flight_number++, current_time, arriving);
            if (small_airport.can_land(current_plane) != success)
                current_plane.refuse();
            else 
            	current_plane.wait();
        }
//        飞机起飞
        int number_departures = variable.poisson(departure_rate);
        for (int j = 0; j < number_departures; j++) {
        	Plane current_plane(flight_number++, current_time, departing);
           	if (small_airport.can_depart(current_plane) != success)
                current_plane.refuse();
            else
            	current_plane.wait();
        }
        Plane moving_plane;
//        跑道选择着陆或起飞
        switch (small_airport.activity1(current_time, moving_plane)) {
            case land:
                        moving_plane.land(current_time);
                        break;
            case takeof:
                        moving_plane.fly(current_time);
                        break;
            case idle:
                        run_idle(current_time);
        }
    }
//    结束模拟并总结
    small_airport.shut_down(end_time);
	cout<<"\n\t\t\t\t\t\t\t按任意键返回";
	_getch();  
}

void Subpro2(){ //P2 
	int end_time;
    int queue_limit;
    int flight_number = 1; 
    double arrival_rate, departure_rate;
    Random variable;

	cout << "这个机场有两条跑道用于着陆和起飞。" << endl
	    << "在一个时间内有一架飞机可以着陆，有一架飞机可以起飞。" << endl<< endl;
    srand((unsigned)time(NULL));
	initialize(end_time, queue_limit, arrival_rate, departure_rate,true);
    Runway small_airport(queue_limit);
	
	for (int current_time = 0; current_time < end_time; current_time++) {
//        飞机降落
        int number_arrivals = variable.poisson(arrival_rate);
        for (int i = 0; i < number_arrivals; i++) {
            Plane current_plane(flight_number++, current_time, arriving);
            if (small_airport.can_land(current_plane) != success)
                current_plane.refuse();
            else
            	current_plane.wait();
        }
//        飞机起飞
        int number_departures = variable.poisson(departure_rate);
        for (int j = 0; j < number_departures; j++) {
            Plane current_plane(flight_number++, current_time, departing);
            if (small_airport.can_depart(current_plane) != success)
                current_plane.refuse();
            else
            	current_plane.wait();
        }
        Plane moving_plane,moving_plane2;
//        跑道选择着陆或起飞
        switch (small_airport.activity2(current_time, moving_plane, moving_plane2)) {
            case land_and_takeof:
                moving_plane.land(current_time);
                moving_plane2.fly(current_time);
                break;
            case land:
                moving_plane.land(current_time);
                break;
            case takeof:
                moving_plane2.fly(current_time);
                break;
            case idle:
                run_idle(current_time);
        }
    }
//    结束模拟并总结
    small_airport.shut_down(end_time);
	cout<<"\n\t\t\t\t\t\t\t按任意键返回";
	_getch(); 
}

void Subpro3(){ //P3 
	int end_time;
    int queue_limit;
    int flight_number = 1; 
    double arrival_rate, departure_rate;
    Random variable;

	cout << "这个机场有两条跑道用于着陆和起飞。 " << endl
         << "在一个时间内有一架飞机可以着陆，有一架飞机可以起飞。 " << endl
         << "如果某个队列是空的，那么两条跑道均可用于着陆或均可用于起飞。 " << endl<< endl;
    srand((unsigned)time(NULL));
	initialize(end_time, queue_limit, arrival_rate, departure_rate,true);
    Runway small_airport(queue_limit);
	
	for (int current_time = 0; current_time < end_time; current_time++) {
//        飞机降落
        int number_arrivals = variable.poisson(arrival_rate);
        for (int i = 0; i < number_arrivals; i++) {
            Plane current_plane(flight_number++, current_time, arriving);
            if (small_airport.can_land(current_plane) != success)
                current_plane.refuse();
             else 
            	current_plane.wait();
        }
//        飞机起飞
        int number_departures = variable.poisson(departure_rate);
        for (int j = 0; j < number_departures; j++) {
            Plane current_plane(flight_number++, current_time, departing);
            if (small_airport.can_depart(current_plane) != success)
                current_plane.refuse();
             else 
            	current_plane.wait();
        }
        Plane moving_plane,moving_plane2;
//        跑道选择着陆或起飞
        switch (small_airport.activity3(current_time, moving_plane, moving_plane2)) {
            case land_and_takeof:
                moving_plane.land(current_time);
                moving_plane2.fly(current_time);
                break;
            case land:
                moving_plane.land(current_time);
                break;
            case takeof:
                moving_plane2.fly(current_time);
                break;
            case land2:
                moving_plane.land(current_time);
                moving_plane2.land(current_time);
                break;
            case takeof2:
                moving_plane2.fly(current_time);
                moving_plane.fly(current_time);
                break;
            case idle:
                run_idle(current_time);
        }
    }
//    结束模拟并总结
    small_airport.shut_down(end_time);
	cout<<"\n\t\t\t\t\t\t\t按任意键返回";
	_getch(); 
}

void Subpro4(){ //P4 
	int end_time;
    int queue_limit;
    int flight_number = 1; 
    double arrival_rate, departure_rate;
    Random variable;
    
 	cout << "这个机场有三条跑道用于着陆和起飞。 " << endl
         << "在一个时间内有一条跑道可以着陆，有一条跑道可以起飞。 " << endl
         << "第三条跑道用于着陆，如果没有飞机着陆，也可以用于起飞。 " << endl<< endl;
    srand((unsigned)time(NULL));
	initialize(end_time, queue_limit, arrival_rate, departure_rate,true);
    Runway small_airport(queue_limit);
	for (int current_time = 0; current_time < end_time; current_time++) {
//        飞机降落
        int number_arrivals = variable.poisson(arrival_rate);
        for (int i = 0; i < number_arrivals; i++) {
            Plane current_plane(flight_number++, current_time, arriving);
            if (small_airport.can_land(current_plane) != success)
                current_plane.refuse();
             else 
            	current_plane.wait();
        }
//        飞机起飞
        int number_departures = variable.poisson(departure_rate);
        for (int j = 0; j < number_departures; j++) {
            Plane current_plane(flight_number++, current_time, departing);
            if (small_airport.can_depart(current_plane) != success)
                current_plane.refuse();
             else 
            	current_plane.wait();
        }
        Plane moving_plane,moving_plane2,moving_plane3;
//        跑道选择着陆或起飞
        switch (small_airport.activity4(current_time, moving_plane, moving_plane2 ,moving_plane3)) {
            case land2_and_takeof:
                moving_plane.land(current_time);
                moving_plane2.land(current_time);
                moving_plane3.fly(current_time);
                break;
            case land_and_takeof2:
                moving_plane.land(current_time);
                moving_plane2.fly(current_time);
                moving_plane3.fly(current_time);
                break;
            case land_and_takeof:
                moving_plane.land(current_time);
                moving_plane2.fly(current_time);
                break;
            case land:
                moving_plane.land(current_time);
                break;
            case takeof:
                moving_plane2.fly(current_time);
                break;
            case land2:
                moving_plane.land(current_time);
                moving_plane2.land(current_time);
                break;
            case takeof2:
                moving_plane2.fly(current_time);
                moving_plane.fly(current_time);
                break;
            case idle:
                run_idle(current_time);
        }
    }
//    结束模拟并总结
    small_airport.shut_down(end_time);

	cout<<"\n\t\t\t\t\t\t\t按任意键返回";
	_getch(); 
}

void Subpro5(){ //P5 
	int end_time;
    int queue_limit;
    int flight_number = 1; 
    double arrival_rate, departure_rate;
    Random variable;
    
	cout << "这个机场只有一条跑道用于着陆和起飞。" << endl
    	<< "在一个时间内只有一架飞机可以着陆或者起飞。" << endl
    	<<"考虑飞机燃料剩余量，优先让剩余量少的降落。"<< endl<<endl; 
    srand((unsigned)time(NULL));
	initialize(end_time, queue_limit, arrival_rate, departure_rate,false);
    Runway small_airport(queue_limit,1000);
	
	for (int current_time = 0; current_time < end_time; current_time++) {
//        飞机降落
        int number_arrivals = variable.poisson(arrival_rate);
        for (int i = 0; i < number_arrivals; i++) {
            Plane current_plane(flight_number++, current_time, arriving);
            small_airport.can_land2(current_plane);
            current_plane.wait2();
        }
//        飞机起飞
        int number_departures = variable.poisson(departure_rate);
        for (int j = 0; j < number_departures; j++) {
        	Plane current_plane(flight_number++, current_time, departing);
           	if (small_airport.can_depart(current_plane) != success)
                current_plane.refuse();
            else
            	current_plane.wait();
        }
        Plane moving_plane;
//        跑道选择着陆或起飞
        switch (small_airport.activity5(current_time, moving_plane)) {
            case land:
                        moving_plane.land(current_time);
                        break;
            case takeof:
                        moving_plane.fly(current_time);
                        break;
            case idle:
                        run_idle(current_time);
        }
    }
//    结束模拟并总结
    small_airport.shut_down(end_time); 
	cout<<"\n\t\t\t\t\t\t\t按任意键返回";
	_getch(); 	 
}

void Subpro6(){ //P6 
	int end_time;
    int queue_limit;
    int flight_number = 1;  
    Random variable;
    
	cout << "这个机场只有一条跑道用于着陆和起飞。" << endl
    	<< "在一个时间内只有一架飞机可以着陆或者起飞。" << endl
    	<< "着陆和起飞的飞机数量由用户输入决定。" << endl << endl; 
    srand((unsigned)time(NULL));
	initialize(end_time, queue_limit);
    Runway small_airport(queue_limit);
	for (int current_time = 0; current_time < end_time; current_time++) {
//        飞机降落
        pair<int, int> a = variable.set(current_time);
        int number_arrivals = a.first;
        for (int i = 0; i < number_arrivals; i++) {
            Plane current_plane(flight_number++, current_time, arriving);
            if (small_airport.can_land(current_plane) != success)
                current_plane.refuse();
             else 
            	current_plane.wait();
        }
//        飞机起飞
        int number_departures = a.second;
        for (int j = 0; j < number_departures; j++) {
            Plane current_plane(flight_number++, current_time, departing);
            if (small_airport.can_depart(current_plane) != success)
                current_plane.refuse();
             else 
            	current_plane.wait();
        }
        Plane moving_plane;
//        跑道选择着陆或起飞
        switch (small_airport.activity1(current_time, moving_plane)) {
            case land:
                        moving_plane.land(current_time);
                        break;
            case takeof:
                        moving_plane.fly(current_time);
                        break;
            case idle:
                        run_idle(current_time);
        }
    }
//    结束模拟并总结
    small_airport.shut_down(end_time);
	cout<<"\n\t\t\t\t\t\t\t按任意键返回";
	_getch(); 	 
} 
