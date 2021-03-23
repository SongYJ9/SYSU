#include <iostream>
#include <vector>
#include <stack>
#include <conio.h>
#include <fstream>
#include <iomanip>
#include <time.h>
#include <windows.h>
const int MAX = 16;
const int INF = 10000 ;
using namespace std;

struct Node{
	string Name;
	string intruction;
	int visitcount;
	Node(){
		Name="";
		intruction="";
		visitcount=0;
	} 
	Node(string a,string b,int cou=0){
		Name = a;
		intruction = b;
		visitcount = cou;
	}
};

Node* name[MAX];
int m_dw[MAX][MAX]={ 0  ,180,180,350,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,//0
						180,0  ,INF,300,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,//1
						180,INF,0  ,200,450,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,//2
						350,300,200,0  ,INF,220,120,INF,INF,INF,INF,INF,INF,INF,INF,INF,//3
						INF,INF,450,INF,0  ,140,INF,140,INF,INF,INF,INF,INF,INF,INF,INF,//4
						INF,INF,INF,220,140,0  ,220,220,INF,260,INF,INF,INF,INF,INF,INF,//5
						INF,INF,INF,120,INF,220,0  ,INF,50 ,INF,INF,INF,INF,INF,INF,INF,//6
						INF,INF,INF,INF,140,220,INF,0  ,INF,260,INF,INF,INF,INF,INF,INF,//7
						INF,INF,INF,INF,INF,INF,50 ,INF,0  ,370,INF,250,INF,INF,INF,INF,//8
						INF,INF,INF,INF,INF,260,INF,260,370,0  ,60 ,INF,120,INF,INF,INF,//9
						INF,INF,INF,INF,INF,INF,INF,INF,INF,60 ,0  ,100,160,INF,INF,INF,//10
						INF,INF,INF,INF,INF,INF,INF,INF,250,INF,100,0  ,INF,120,INF,INF,//11
						INF,INF,INF,INF,INF,INF,INF,INF,INF,120,160,INF,0  ,120,200,INF,//12
						INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,120,120,0  ,120,120,//13
						INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,200,120,0  ,150,//14
						INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,120,150,0   //15
						}; 
int m_dc[MAX][MAX]={0  ,180,180,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,
						180,0  ,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,
						180,INF,0  ,INF,450,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,
						INF,INF,INF,0  ,INF,220,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,
						INF,INF,450,INF,0  ,140,INF,140,INF,INF,INF,INF,INF,INF,INF,INF,
						INF,INF,INF,220,140,0  ,220,220,INF,260,INF,INF,INF,INF,INF,INF,
						INF,INF,INF,INF,INF,220,0  ,INF,INF,INF,INF,INF,INF,INF,INF,INF,
						INF,INF,INF,INF,140,220,INF,0  ,INF,INF,INF,INF,INF,INF,INF,INF,
						INF,INF,INF,INF,INF,INF,INF,INF,0  ,370,INF,INF,INF,INF,INF,INF,
						INF,INF,INF,INF,INF,260,INF,INF,370,0  ,INF,INF,120,INF,INF,INF,
						INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,0  ,INF,160,INF,INF,INF,
						INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,0  ,INF,120,INF,INF,
						INF,INF,INF,INF,INF,INF,INF,INF,INF,120,160,INF,0  ,120,200,INF,
						INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,120,120,0  ,120,120,
						INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,200,120,0  ,150,
						INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,120,150,0  
						};

bool Find(int a,int s[100],int d); //判断a在不在s里 
void Menu(); 		// 输出主菜单 
void Initial(); 	// 程序启动的初始化操作 

void Introduce();	//地点简介 
void GetRoute();	//查询最短路径 
void Rank();		//景点访问排行榜 
void FreeSpace(); 	//结束程序时回收内存空间
void FileRead(); 	// 读取文件信息 
void FileWrite();	// 修改并关闭文件 
 
int main(){
	Initial();
	while(1){
		Menu();
		char x;
		do{
			x=_getch();
		} while((x<'1' or x>'5') and x!='q' and x!='Q');
		if(x=='q' or x=='Q'){
			FileWrite();
			FreeSpace();
			break; 
		}
		system("cls");
		switch(x){
			case '1':
				Introduce();
				break;
			case '2':
				GetRoute();
				break;
			case '3':
				Rank();
				break;
			case '4':
				system("模拟地图.png");
				break;
			case '5':
				system("c#项目4.exe");
				break;
		}
		system("cls");
	}
}

bool Find(int a,int s[100],int d) //a：看a在不在s里，d：s共有多少个元素 
{
	for(int i = 0; i < d; i++)
	{
		if(s[i] == a)
			return true;
	}
	return false;
}

void Menu(){
	cout << endl << endl ;
	cout << "\t\t----------------------" << endl; 
	cout << "\t\t  *中山大学导游咨询*  " << endl; 
	cout << "\t\t----------------------" << endl;
	cout << "\t  1.查看中山大学主要景点及其信息" << endl;
	cout << "\t  2.查询两个地点间的最短路径" << endl;
	cout << "\t  3.中大景点热门排行" << endl;
	cout << "\t  4.查看中大模拟地图" << endl;
	cout << "\t  5.嫌这个太丑？点这里！" << endl;
	cout << "\t  q.退出" << endl;
	cout << "\t-----------------------------------" <<endl<<endl; 
	cout << "\t请输入对应编码选择您所需的操作： " ; 
}
void Initial(){
	name[0]=new Node("牌坊","整座门楼用钢筋三合土筑成，外饰面用花岗石砌成。高10.98米，宽25.315米。门额刻有“国立中山大学”六个大字");
	name[1]=new Node("数据科学与计算机学院","中山大学整合了之前好几个学院的优势资源，组建了数据科学与计算机学院。");
	name[2]=new Node("行政楼","行政办公的地方"); 
	name[3]=new Node("图书馆","又称中东自习室，位置不多，晚点来不好找位置做作业；曾经是中东目测最大建筑，不过现在被啥化学学院楼取代了");
	name[4]=new Node("南/北实验楼","同学们平时打码、做祭祖等其他实验的地方，以及许多老师的办公室和实验室也设在里面");
	name[5]=new Node("传播与设计学院","是聚集了一群优质妹子和强势女篮的天堂，但由于院楼构造奇特，又被称为“中东马桶楼”"); 
	name[6]=new Node("体育馆","除了第一节体育课用来集合之外，还可以用作礼堂和其他活动场所，租金好像是一天两万"); 
	name[7]=new Node("工学院","除了建筑面前的小广场可以用来举办活动之外，还真不知道有啥其他用处"); 
	name[8]=new Node("校门","学生们上学的唯二通道。曾经因为中大修校门事件被称为“狗洞”，但是其实说的也挺合理的"); 
	name[9]=new Node("地道","学生们上学的唯二通道，单车党飙车圣地，但是爬坡的时候就会特别累"); 
	name[10]=new Node("明德园六号","聚集了快递点、理发店、银行等众多日常设施的地方，偶尔也能申请三楼房间用于搞活动"); 
	name[11]=new Node("明德园","中东宿舍楼之一，特点是离教学区和明六比较近"); 
	name[12]=new Node("格致园","中东宿舍楼之一，特点是供奉着深圳校区的学生们"); 
	name[13]=new Node("饭堂","大致分为四个饭堂，一、二、四饭比较普通，三饭比较好吃比较贵(并不是"); 
	name[14]=new Node("慎思园","中东宿舍楼之一，特点是南校门封了之后就变得比较偏僻，注意慎思园是没有1-4号的哦"); 
	name[15]=new Node("至善园","中东宿舍楼之一，特点是住着我们院的女生！！！！");   
	FileRead();
}

void Introduce(){
	int a; 
	bool flag = false;  //控制界面显示 
	Int:
	system("cls");
	cout<<"\n";
	for(int i=0;i<MAX;i++){
		cout << i+1 << ". " << name[i]->Name << endl;
	}
	cout << "--------------------------------------" << endl; 
	if(flag){
		name[a-1]->visitcount+=1; 
		cout << endl << "景点名字： " << name[a-1]->Name << endl;
		cout << "简介： " << name[a-1]->intruction << endl;
		cout << "热度:  " << name[a-1]->visitcount <<endl; 
		cout << "--------------------------------------" << endl; 
	}
	cout << "请输入要查询的景点的编码(按0退出查询): ";
	cin >> a;
	if(!cin.good() or a<0 or a>16){
		cout << "输入错误，请重新输入!";
		cin.clear();
		cin.sync();
		Sleep(500);
		flag = false;
		goto Int;
	}	
	if(a==0) return;
	else{
		flag = true;
		cin.clear();
		cin.sync();  
		goto Int;
	}
				 
}
void GetRoute(){
	int sta; //起点 
	int dst; //终点 
	bool flag1 = false;  //控制界面显示 
	bool flag2 = false;  //控制界面显示 
	GRT:
	system("cls");
	cout<<"\n";
	for(int i=0;i<MAX;i++){
		cout << i+1 << ". " << name[i]->Name << endl;
	}
	cout << "--------------------------------------" << endl; 
	if(!flag1){
		cout << "请输入路径的起点(按0退出查询): ";
		cin >> sta;
		if(!cin.good() or sta<0 or sta>16){
			cout << "输入错误，请重新输入!";
			cin.clear();
			cin.sync();
			Sleep(500);
			flag1 = false;
			goto GRT;
		}	
		if(sta==0) return;
		else{
			flag1 = true;
			cin.clear();
			cin.sync();  
			goto GRT;
		} 
	}else if(flag1 and !flag2){
		cout << "起点： "<<name[sta-1]->Name <<endl; 
		cout << "--------------------------------------" << endl;
		cout << "请输入路径的终点(按0退出查询): ";
		cin >> dst;
		if(!cin.good() or dst<0 or dst>16){
			cout << "输入错误，请重新输入!";
			cin.clear();
			cin.sync();
			Sleep(500);
			flag2 = false;
			goto GRT;
		}	
		if(dst==0) return;
		else{
			flag2 = true;
			cin.clear();
			cin.sync();  
			goto GRT;
		} 
	}else if(flag1 and flag2){
		cout << "起点： "<<name[sta-1]->Name <<endl; 
		cout << "终点： "<<name[dst-1]->Name <<endl; 
		cout << "--------------------------------------" << endl;
		
		//搞个车车！！！ 
		int x1 = sta-1;
		int x2 = dst-1;
		int Dis[MAX];//距离，会不断刷新 
		bool S1[MAX]={0};
		string DD[MAX];//show the path
		for(int i=0;i<MAX;i++){
			Dis[i]=m_dc[x1][i];
			S1[i]=false;
			DD[i]="";
		} 
		S1[x1]=1;
		DD[x1]=name[x1]->Name;
		int which1=0;
		int which2=0;
		while(!S1[x2]){
			int MIN=INF;
			int i,j;
			for(i=0;i<MAX;i++){
				for(j=0;j<MAX;j++){
					if(S1[i]==1 && m_dc[i][j]!=INF && m_dc[i][j]!=0 && S1[j]==0){
						if(Dis[j]>Dis[i]+m_dc[i][j])
							Dis[j]=Dis[i]+m_dc[i][j];
						if(MIN>Dis[j]){
							MIN=Dis[j];
							which1=i;
							which2=j;
						}
					}
				}
			}
			S1[which2]=1;
			DD[which2]=DD[which1]+ " -> " + name[which2]->Name;
		}
		cout << "开车最短距离： " << Dis[x2] << "米" << endl;
		cout << "开车路径： " << DD[x2] << endl;	
		
		
		
		for(int i=0;i<MAX;i++){
			Dis[i]=m_dw[x1][i];
			S1[i]=false;
			DD[i]="";
		} 
		S1[x1]=1;
		DD[x1]=name[x1]->Name;
		which1=0;
		which2=0;
		while(!S1[x2]){
			int MIN=INF;
			int i,j;
			for(i=0;i<MAX;i++){
				for(j=0;j<MAX;j++){
					if(S1[i]==1 && m_dw[i][j]!=INF && m_dw[i][j]!=0 && S1[j]==0){
						if(Dis[j]>Dis[i]+m_dw[i][j])
							Dis[j]=Dis[i]+m_dw[i][j];
						if(MIN>Dis[j]){
							MIN=Dis[j];
							which1=i;
							which2=j;
						}
					}
				}
			}
			S1[which2]=1;
			DD[which2]=DD[which1]+ " -> " + name[which2]->Name;
		}
		
		cout << "步行最短距离： " << Dis[x2] << "米" << endl;
		cout << "步行路径： " << DD[x2] << endl;	
		
		cout<<"\n\n\t\t\t按任意键继续...";
		_getch();
		flag1 = false;
		flag2 = false;
		name[sta-1]->visitcount+=1;
		name[dst-1]->visitcount+=1;
		goto GRT;
	}
}

void Rank(){
	Node* rank[MAX];
	for(int i=0;i<MAX;i++)
		rank[i] = name[i];
	// 从大到小排序 
	for(int i=0;i<MAX-1;i++){
		for(int j=0;j<MAX-i-1;j++){
			if(rank[j]->visitcount<rank[j+1]->visitcount){
				Node* tmp = rank[j];
				rank[j] = rank[j+1];
				rank[j+1] = tmp; 
			}
		}
	}
	cout<<"\n\n";
	cout<<"\t\t景点热度排行榜\n\n";
	cout<<"\t景点\t\t\t热度\n\n";
	for(int i=0;i<MAX;i++){
		cout.setf(ios::left);
		cout<<"\t"<<setw(25)<<rank[i]->Name<<rank[i]->visitcount<<endl; 
	}		
	cout<<"\n\n\t\t\t\t按任意键放回...";
	_getch();
}

void FileRead(){
	ifstream read("景点热度.txt",ios::in);
	if(!read){
		ofstream write("景点热度.txt",ios::out);
		if(write.is_open()){
			for(int i=0;i<MAX;i++){
				write<<name[i]->Name<<"\t"<<name[i]->visitcount<<endl; 
			}
			write.close();
		}
	}else{
		int cou;
		string na;
		for(int i=0;i<MAX;i++){
			read>>na>>cou;
			name[i]->visitcount = cou;
		}
		read.close(); 
	}
}
void FileWrite(){
	ofstream write("景点热度.txt",ios::out);
	if(write.is_open()){
		for(int i=0;i<MAX;i++){
			write<<name[i]->Name<<"\t"<<name[i]->visitcount<<endl; 
		}
		write.close();
	}
}
void FreeSpace(){
	for(int i=0;i<MAX;i++)
		delete name[i];	
} 
