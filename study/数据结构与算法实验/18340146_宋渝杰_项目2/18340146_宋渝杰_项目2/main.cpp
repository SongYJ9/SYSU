#include<iostream>
#include<conio.h>
#include<windows.h>
#include"Function.hpp"
using namespace std;

//��main�������ѹ��ܺ������������嵥�����ļ� 
int main(){

	void (*Menu_Funp[6])(void);   // ��ʼҳ����ָ�� 
	Menu_Funp[0]=Subpro1; Menu_Funp[1]=Subpro2; Menu_Funp[2]=Subpro3; 
	Menu_Funp[3]=Subpro4; Menu_Funp[4]=Subpro5; Menu_Funp[5]=Subpro6; 
	ME:
	Menu();  // ���˵�������� 
	char inp;
	do{
		inp = _getch();
	}while(inp!='1'&&inp!='2'&&inp!='3'&&inp!='4'&&inp!='5'&&inp!='6'&&inp!='q');
	cout<<inp;
	if(inp=='q'){
		return 0;
	} 
	system("cls");		// ���� 
	Menu_Funp[inp-'1']();  //ʵ����Ӧ���� 
	system("cls");
	goto ME; // ʵ��ѭ�����ܣ����û������˳����� 
}
