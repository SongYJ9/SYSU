#include<iostream>
#include<conio.h>
#include<windows.h>
#include"Function.hpp"
using namespace std;

//简化main函数，把功能函数声明及定义单独成文件 
int main(){

	void (*Menu_Funp[6])(void);   // 起始页函数指针 
	Menu_Funp[0]=Subpro1; Menu_Funp[1]=Subpro2; Menu_Funp[2]=Subpro3; 
	Menu_Funp[3]=Subpro4; Menu_Funp[4]=Subpro5; Menu_Funp[5]=Subpro6; 
	ME:
	Menu();  // 主菜单界面输出 
	char inp;
	do{
		inp = _getch();
	}while(inp!='1'&&inp!='2'&&inp!='3'&&inp!='4'&&inp!='5'&&inp!='6'&&inp!='q');
	cout<<inp;
	if(inp=='q'){
		return 0;
	} 
	system("cls");		// 清屏 
	Menu_Funp[inp-'1']();  //实现相应功能 
	system("cls");
	goto ME; // 实现循环功能，由用户决定退出程序 
}
