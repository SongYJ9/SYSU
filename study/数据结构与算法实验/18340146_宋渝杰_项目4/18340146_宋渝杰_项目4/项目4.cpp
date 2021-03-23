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

bool Find(int a,int s[100],int d); //�ж�a�ڲ���s�� 
void Menu(); 		// ������˵� 
void Initial(); 	// ���������ĳ�ʼ������ 

void Introduce();	//�ص��� 
void GetRoute();	//��ѯ���·�� 
void Rank();		//����������а� 
void FreeSpace(); 	//��������ʱ�����ڴ�ռ�
void FileRead(); 	// ��ȡ�ļ���Ϣ 
void FileWrite();	// �޸Ĳ��ر��ļ� 
 
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
				system("ģ���ͼ.png");
				break;
			case '5':
				system("c#��Ŀ4.exe");
				break;
		}
		system("cls");
	}
}

bool Find(int a,int s[100],int d) //a����a�ڲ���s�d��s���ж��ٸ�Ԫ�� 
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
	cout << "\t\t  *��ɽ��ѧ������ѯ*  " << endl; 
	cout << "\t\t----------------------" << endl;
	cout << "\t  1.�鿴��ɽ��ѧ��Ҫ���㼰����Ϣ" << endl;
	cout << "\t  2.��ѯ�����ص������·��" << endl;
	cout << "\t  3.�д󾰵���������" << endl;
	cout << "\t  4.�鿴�д�ģ���ͼ" << endl;
	cout << "\t  5.�����̫�󣿵����" << endl;
	cout << "\t  q.�˳�" << endl;
	cout << "\t-----------------------------------" <<endl<<endl; 
	cout << "\t�������Ӧ����ѡ��������Ĳ����� " ; 
}
void Initial(){
	name[0]=new Node("�Ʒ�","������¥�øֽ����������ɣ��������û���ʯ���ɡ���10.98�ף���25.315�ס��Ŷ���С�������ɽ��ѧ����������");
	name[1]=new Node("���ݿ�ѧ������ѧԺ","��ɽ��ѧ������֮ǰ�ü���ѧԺ��������Դ���齨�����ݿ�ѧ������ѧԺ��");
	name[2]=new Node("����¥","�����칫�ĵط�"); 
	name[3]=new Node("ͼ���","�ֳ��ж���ϰ�ң�λ�ò��࣬�����������λ������ҵ���������ж�Ŀ����������������ڱ�ɶ��ѧѧԺ¥ȡ����");
	name[4]=new Node("��/��ʵ��¥","ͬѧ��ƽʱ���롢�����������ʵ��ĵط����Լ������ʦ�İ칫�Һ�ʵ����Ҳ��������");
	name[5]=new Node("���������ѧԺ","�Ǿۼ���һȺ�������Ӻ�ǿ��Ů�������ã�������Ժ¥�������أ��ֱ���Ϊ���ж���Ͱ¥��"); 
	name[6]=new Node("������","���˵�һ����������������֮�⣬�������������ú��������������������һ������"); 
	name[7]=new Node("��ѧԺ","���˽�����ǰ��С�㳡���������ٰ�֮�⣬���治֪����ɶ�����ô�"); 
	name[8]=new Node("У��","ѧ������ѧ��Ψ��ͨ����������Ϊ�д���У���¼�����Ϊ����������������ʵ˵��Ҳͦ�����"); 
	name[9]=new Node("�ص�","ѧ������ѧ��Ψ��ͨ����������쭳�ʥ�أ��������µ�ʱ��ͻ��ر���"); 
	name[10]=new Node("����԰����","�ۼ��˿�ݵ㡢���ꡢ���е��ڶ��ճ���ʩ�ĵط���ż��Ҳ��������¥�������ڸ�"); 
	name[11]=new Node("����԰","�ж�����¥֮һ���ص������ѧ���������ȽϽ�"); 
	name[12]=new Node("����԰","�ж�����¥֮һ���ص��ǹ���������У����ѧ����"); 
	name[13]=new Node("����","���·�Ϊ�ĸ����ã�һ�������ķ��Ƚ���ͨ�������ȽϺóԱȽϹ�(������"); 
	name[14]=new Node("��˼԰","�ж�����¥֮һ���ص�����У�ŷ���֮��ͱ�ñȽ�ƫƧ��ע����˼԰��û��1-4�ŵ�Ŷ"); 
	name[15]=new Node("����԰","�ж�����¥֮һ���ص���ס������Ժ��Ů����������");   
	FileRead();
}

void Introduce(){
	int a; 
	bool flag = false;  //���ƽ�����ʾ 
	Int:
	system("cls");
	cout<<"\n";
	for(int i=0;i<MAX;i++){
		cout << i+1 << ". " << name[i]->Name << endl;
	}
	cout << "--------------------------------------" << endl; 
	if(flag){
		name[a-1]->visitcount+=1; 
		cout << endl << "�������֣� " << name[a-1]->Name << endl;
		cout << "��飺 " << name[a-1]->intruction << endl;
		cout << "�ȶ�:  " << name[a-1]->visitcount <<endl; 
		cout << "--------------------------------------" << endl; 
	}
	cout << "������Ҫ��ѯ�ľ���ı���(��0�˳���ѯ): ";
	cin >> a;
	if(!cin.good() or a<0 or a>16){
		cout << "�����������������!";
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
	int sta; //��� 
	int dst; //�յ� 
	bool flag1 = false;  //���ƽ�����ʾ 
	bool flag2 = false;  //���ƽ�����ʾ 
	GRT:
	system("cls");
	cout<<"\n";
	for(int i=0;i<MAX;i++){
		cout << i+1 << ". " << name[i]->Name << endl;
	}
	cout << "--------------------------------------" << endl; 
	if(!flag1){
		cout << "������·�������(��0�˳���ѯ): ";
		cin >> sta;
		if(!cin.good() or sta<0 or sta>16){
			cout << "�����������������!";
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
		cout << "��㣺 "<<name[sta-1]->Name <<endl; 
		cout << "--------------------------------------" << endl;
		cout << "������·�����յ�(��0�˳���ѯ): ";
		cin >> dst;
		if(!cin.good() or dst<0 or dst>16){
			cout << "�����������������!";
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
		cout << "��㣺 "<<name[sta-1]->Name <<endl; 
		cout << "�յ㣺 "<<name[dst-1]->Name <<endl; 
		cout << "--------------------------------------" << endl;
		
		//������������� 
		int x1 = sta-1;
		int x2 = dst-1;
		int Dis[MAX];//���룬�᲻��ˢ�� 
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
		cout << "������̾��룺 " << Dis[x2] << "��" << endl;
		cout << "����·���� " << DD[x2] << endl;	
		
		
		
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
		
		cout << "������̾��룺 " << Dis[x2] << "��" << endl;
		cout << "����·���� " << DD[x2] << endl;	
		
		cout<<"\n\n\t\t\t�����������...";
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
	// �Ӵ�С���� 
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
	cout<<"\t\t�����ȶ����а�\n\n";
	cout<<"\t����\t\t\t�ȶ�\n\n";
	for(int i=0;i<MAX;i++){
		cout.setf(ios::left);
		cout<<"\t"<<setw(25)<<rank[i]->Name<<rank[i]->visitcount<<endl; 
	}		
	cout<<"\n\n\t\t\t\t��������Ż�...";
	_getch();
}

void FileRead(){
	ifstream read("�����ȶ�.txt",ios::in);
	if(!read){
		ofstream write("�����ȶ�.txt",ios::out);
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
	ofstream write("�����ȶ�.txt",ios::out);
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
