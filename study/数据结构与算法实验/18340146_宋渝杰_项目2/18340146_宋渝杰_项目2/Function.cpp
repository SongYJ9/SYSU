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

void initialize(int &end_time, int &queue_limit,double &arrival_rate, double &departure_rate,int flag){ //P1-P5�����뺯�� 
    if(flag) cout << "-�������ʱ��ȴ���½������ɵķɻ����������Ŀ�Ƕ��٣� "<< flush;
    else cout << "-�������ʱ��ȴ���ɵķɻ����������Ŀ�Ƕ��٣� "<< flush;
   	CI1:
	fflush(stdin);
    cin >> queue_limit;
    if(!cin.good() or queue_limit<=0){
    	cin.clear(); cin.sync();
    	cerr << "--�������,����������: ";
		goto CI1;
    }
      
    cout << "-ģ��೤��ʱ�䣿 " << flush;
    CI2:
    fflush(stdin);
	cin >> end_time;
    if(!cin.good() or end_time<=0){
    	cin.clear(); cin.sync();
    	cerr << "--�������,����������: ";
		goto CI2;
    }
    
    cout << "-ƽ��һ��ʱ���ж��ټܷɻ����䣿 " << flush;
    CI3:
    fflush(stdin);
	cin >> arrival_rate;
    if(!cin.good() or arrival_rate<=0){
    	cin.clear(); cin.sync();
    	cerr << "--�������,����������: ";
		goto CI3;
    }
    cout << "-ƽ��һ��ʱ���ж��ټܷɻ���ɣ� " << flush;
    CI4:
    fflush(stdin);
	cin >> departure_rate;
    if(!cin.good() or departure_rate<=0){
    	cin.clear(); cin.sync();
    	cerr << "--�������,����������: ";
		goto CI4;
    }
        
  
}

void initialize(int &end_time, int &queue_limit){ //P6���뺯�� 
    
    cout << "-�������ʱ��ȴ���½������ɵķɻ����������Ŀ�Ƕ��٣� "<< flush;
    CL1:
    fflush(stdin);
	cin >> queue_limit;
	if(!cin.good() or queue_limit<=0){
    	cin.clear(); cin.sync();
    	cerr << "--�������,����������: ";
		goto CL1;
    }
    cout << "-ģ��೤��ʱ�䣿 " << flush;
    CL2: 
	fflush(stdin);
    cin >> end_time;
    if(!cin.good() or end_time<=0){
    	cin.clear(); cin.sync();
    	cerr << "--�������,����������: ";
		goto CL2;
    }
}

void run_idle(int time){
    cout << time << ": �ܵ������õġ� " << endl;
}

void Menu(){ //�˵���ʾ 
	Base_Print();
	cout<<"\n\t\t\t\t\t\t    �� ʼ ҳ"; 
	cout<<"\n\n\n";
	cout<<"\t\t\t\t\t(1) ����һ";	
	cout<<"\t\t(2) ������\n\n";	
	cout<<"\t\t\t\t\t(3) ������";	
	cout<<"\t\t(4) ������\n\n";
	cout<<"\t\t\t\t\t(5) ������";	
	cout<<"\t\t(6) ������\n\n";
	cout<<"\t\t\t\t\t(q) ��������\n";			
	cout<<"\n\t\t\t\t������ָ��(�������):";			
}

void Base_Print(){
	cout<<"\n";
	cout<<"\t\t\t\t\t  ----------------------------"<<endl;
	cout<<"\t\t\t\t\t  |��  ��  ��  ��  ��  ��  ��|"<<endl;
	cout<<"\t\t\t\t\t  ----------------------------"<<endl;
}

void Subpro1(){ //P1 
	int end_time;
    int queue_limit;
    int flight_number = 1; 
    double arrival_rate, departure_rate;
    Random variable;
    
	cout << "�������ֻ��һ���ܵ�������½����ɡ�" << endl
    	<< "��һ��ʱ����ֻ��һ�ܷɻ�������½������ɡ�" << endl<< endl;;
    srand((unsigned)time(NULL));
	initialize(end_time, queue_limit, arrival_rate, departure_rate,true);
    Runway small_airport(queue_limit);
	
	for (int current_time = 0; current_time < end_time; current_time++) {
//        �ɻ�����
        int number_arrivals = variable.poisson(arrival_rate);
        for (int i = 0; i < number_arrivals; i++) {
            Plane current_plane(flight_number++, current_time, arriving);
            if (small_airport.can_land(current_plane) != success)
                current_plane.refuse();
            else 
            	current_plane.wait();
        }
//        �ɻ����
        int number_departures = variable.poisson(departure_rate);
        for (int j = 0; j < number_departures; j++) {
        	Plane current_plane(flight_number++, current_time, departing);
           	if (small_airport.can_depart(current_plane) != success)
                current_plane.refuse();
            else
            	current_plane.wait();
        }
        Plane moving_plane;
//        �ܵ�ѡ����½�����
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
//    ����ģ�Ⲣ�ܽ�
    small_airport.shut_down(end_time);
	cout<<"\n\t\t\t\t\t\t\t�����������";
	_getch();  
}

void Subpro2(){ //P2 
	int end_time;
    int queue_limit;
    int flight_number = 1; 
    double arrival_rate, departure_rate;
    Random variable;

	cout << "��������������ܵ�������½����ɡ�" << endl
	    << "��һ��ʱ������һ�ܷɻ�������½����һ�ܷɻ�������ɡ�" << endl<< endl;
    srand((unsigned)time(NULL));
	initialize(end_time, queue_limit, arrival_rate, departure_rate,true);
    Runway small_airport(queue_limit);
	
	for (int current_time = 0; current_time < end_time; current_time++) {
//        �ɻ�����
        int number_arrivals = variable.poisson(arrival_rate);
        for (int i = 0; i < number_arrivals; i++) {
            Plane current_plane(flight_number++, current_time, arriving);
            if (small_airport.can_land(current_plane) != success)
                current_plane.refuse();
            else
            	current_plane.wait();
        }
//        �ɻ����
        int number_departures = variable.poisson(departure_rate);
        for (int j = 0; j < number_departures; j++) {
            Plane current_plane(flight_number++, current_time, departing);
            if (small_airport.can_depart(current_plane) != success)
                current_plane.refuse();
            else
            	current_plane.wait();
        }
        Plane moving_plane,moving_plane2;
//        �ܵ�ѡ����½�����
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
//    ����ģ�Ⲣ�ܽ�
    small_airport.shut_down(end_time);
	cout<<"\n\t\t\t\t\t\t\t�����������";
	_getch(); 
}

void Subpro3(){ //P3 
	int end_time;
    int queue_limit;
    int flight_number = 1; 
    double arrival_rate, departure_rate;
    Random variable;

	cout << "��������������ܵ�������½����ɡ� " << endl
         << "��һ��ʱ������һ�ܷɻ�������½����һ�ܷɻ�������ɡ� " << endl
         << "���ĳ�������ǿյģ���ô�����ܵ�����������½�����������ɡ� " << endl<< endl;
    srand((unsigned)time(NULL));
	initialize(end_time, queue_limit, arrival_rate, departure_rate,true);
    Runway small_airport(queue_limit);
	
	for (int current_time = 0; current_time < end_time; current_time++) {
//        �ɻ�����
        int number_arrivals = variable.poisson(arrival_rate);
        for (int i = 0; i < number_arrivals; i++) {
            Plane current_plane(flight_number++, current_time, arriving);
            if (small_airport.can_land(current_plane) != success)
                current_plane.refuse();
             else 
            	current_plane.wait();
        }
//        �ɻ����
        int number_departures = variable.poisson(departure_rate);
        for (int j = 0; j < number_departures; j++) {
            Plane current_plane(flight_number++, current_time, departing);
            if (small_airport.can_depart(current_plane) != success)
                current_plane.refuse();
             else 
            	current_plane.wait();
        }
        Plane moving_plane,moving_plane2;
//        �ܵ�ѡ����½�����
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
//    ����ģ�Ⲣ�ܽ�
    small_airport.shut_down(end_time);
	cout<<"\n\t\t\t\t\t\t\t�����������";
	_getch(); 
}

void Subpro4(){ //P4 
	int end_time;
    int queue_limit;
    int flight_number = 1; 
    double arrival_rate, departure_rate;
    Random variable;
    
 	cout << "��������������ܵ�������½����ɡ� " << endl
         << "��һ��ʱ������һ���ܵ�������½����һ���ܵ�������ɡ� " << endl
         << "�������ܵ�������½�����û�зɻ���½��Ҳ����������ɡ� " << endl<< endl;
    srand((unsigned)time(NULL));
	initialize(end_time, queue_limit, arrival_rate, departure_rate,true);
    Runway small_airport(queue_limit);
	for (int current_time = 0; current_time < end_time; current_time++) {
//        �ɻ�����
        int number_arrivals = variable.poisson(arrival_rate);
        for (int i = 0; i < number_arrivals; i++) {
            Plane current_plane(flight_number++, current_time, arriving);
            if (small_airport.can_land(current_plane) != success)
                current_plane.refuse();
             else 
            	current_plane.wait();
        }
//        �ɻ����
        int number_departures = variable.poisson(departure_rate);
        for (int j = 0; j < number_departures; j++) {
            Plane current_plane(flight_number++, current_time, departing);
            if (small_airport.can_depart(current_plane) != success)
                current_plane.refuse();
             else 
            	current_plane.wait();
        }
        Plane moving_plane,moving_plane2,moving_plane3;
//        �ܵ�ѡ����½�����
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
//    ����ģ�Ⲣ�ܽ�
    small_airport.shut_down(end_time);

	cout<<"\n\t\t\t\t\t\t\t�����������";
	_getch(); 
}

void Subpro5(){ //P5 
	int end_time;
    int queue_limit;
    int flight_number = 1; 
    double arrival_rate, departure_rate;
    Random variable;
    
	cout << "�������ֻ��һ���ܵ�������½����ɡ�" << endl
    	<< "��һ��ʱ����ֻ��һ�ܷɻ�������½������ɡ�" << endl
    	<<"���Ƿɻ�ȼ��ʣ������������ʣ�����ٵĽ��䡣"<< endl<<endl; 
    srand((unsigned)time(NULL));
	initialize(end_time, queue_limit, arrival_rate, departure_rate,false);
    Runway small_airport(queue_limit,1000);
	
	for (int current_time = 0; current_time < end_time; current_time++) {
//        �ɻ�����
        int number_arrivals = variable.poisson(arrival_rate);
        for (int i = 0; i < number_arrivals; i++) {
            Plane current_plane(flight_number++, current_time, arriving);
            small_airport.can_land2(current_plane);
            current_plane.wait2();
        }
//        �ɻ����
        int number_departures = variable.poisson(departure_rate);
        for (int j = 0; j < number_departures; j++) {
        	Plane current_plane(flight_number++, current_time, departing);
           	if (small_airport.can_depart(current_plane) != success)
                current_plane.refuse();
            else
            	current_plane.wait();
        }
        Plane moving_plane;
//        �ܵ�ѡ����½�����
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
//    ����ģ�Ⲣ�ܽ�
    small_airport.shut_down(end_time); 
	cout<<"\n\t\t\t\t\t\t\t�����������";
	_getch(); 	 
}

void Subpro6(){ //P6 
	int end_time;
    int queue_limit;
    int flight_number = 1;  
    Random variable;
    
	cout << "�������ֻ��һ���ܵ�������½����ɡ�" << endl
    	<< "��һ��ʱ����ֻ��һ�ܷɻ�������½������ɡ�" << endl
    	<< "��½����ɵķɻ��������û����������" << endl << endl; 
    srand((unsigned)time(NULL));
	initialize(end_time, queue_limit);
    Runway small_airport(queue_limit);
	for (int current_time = 0; current_time < end_time; current_time++) {
//        �ɻ�����
        pair<int, int> a = variable.set(current_time);
        int number_arrivals = a.first;
        for (int i = 0; i < number_arrivals; i++) {
            Plane current_plane(flight_number++, current_time, arriving);
            if (small_airport.can_land(current_plane) != success)
                current_plane.refuse();
             else 
            	current_plane.wait();
        }
//        �ɻ����
        int number_departures = a.second;
        for (int j = 0; j < number_departures; j++) {
            Plane current_plane(flight_number++, current_time, departing);
            if (small_airport.can_depart(current_plane) != success)
                current_plane.refuse();
             else 
            	current_plane.wait();
        }
        Plane moving_plane;
//        �ܵ�ѡ����½�����
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
//    ����ģ�Ⲣ�ܽ�
    small_airport.shut_down(end_time);
	cout<<"\n\t\t\t\t\t\t\t�����������";
	_getch(); 	 
} 
