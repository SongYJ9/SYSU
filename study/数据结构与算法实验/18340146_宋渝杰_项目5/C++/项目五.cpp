#include<iostream>
#include<vector>
#include<windows.h>
#include<conio.h>
#include<fstream>
#include<string>
#include<time.h>
#include<algorithm> 
#include<iomanip>
#include"AVLTree.hpp"

using namespace std;

const string Str[INFONUM] = {"����","�绰����","QQ","΢��","����","��ַ","����","�ʱ�","�Ա�","���"}; 
Node* Root[TREENUM];
int Count;  // ͨѶ¼�м�¼������  
vector<string> Class[INFONUM-TREENUM]; // ���ڷ������ 

void Menu(); 		// ������˵� 
void Initial(); 	// ���������ĳ�ʼ������ 
void ShowALL(); 	// ��ʾ��������Ϣ
void FindMember();	//������ʾ���� 
void AddMember();	//��Ӷ���  
void ResMember();	//�޸Ķ��� 
void DelMember();	//ɾ������ 
void Statistics(); // ͳ��ͨѶ¼��Ϣ 

// ��������������ʵ���ض����� 
char GetMember(Node*&node);	//����������Ĺ�ͬ���ֶ����ɺ��������ٴ����� 
void ShowSpecialTraversal(Node* node,int& cou,const int& ind,const string& info); // ɸѡ��ʾ 
void ShowTraversal(Node* node,int& cou); //// ����������Ϣ�����ʾ 
void WriteTraversal(Node* node,ofstream&out); // ����������Ϣд���ļ� 
void FileRead(); 	// ��ȡ�ļ���Ϣ 
void FileWrite();	// �޸Ĳ��ر��ļ� 
void FreeSpace(Node* node);// �ͷſռ� 
bool Find(Node* node,int ind,const string& info); 

int main(){
	Initial();
	while(1){
		Menu();
		char x;
		do{
			x=_getch();
		} while((x<'1' or x>'6') and x!='q' and x!='Q');
		if(x=='q' or x=='Q'){
			FileWrite();
			FreeSpace(Root[0]);
			return 0;
		}
		system("cls");
		switch(x){
			case '1':
				ShowALL();
				break;
			case '2':
				Statistics();
				break;
			case '3':
				FindMember();
				break;
			case '4':
				AddMember();
				break;
			case '5':
				ResMember(); 
				break; 
			case '6':
				DelMember(); 
				break; 
		}
		system("cls");
	}
} 

void Menu(){
	cout<<"\n\n";
	cout<<"\t\t\t\t\t------------------------------------"<<endl;
	cout<<"\t\t\t\t\t | ��     ��     ͨ     Ѷ     ¼ |"<<endl;
	cout<<"\t\t\t\t\t------------------------------------"<<endl;
	cout<<"\n\n\n";
	cout<<"\t\t\t\t\t(1) �鿴ȫ����Ϣ";	
	cout<<"\t(2) ͨѶ¼ͳ�Ʋ�ѯ\n\n";	
	cout<<"\t\t\t\t\t(3) ��ѯ��ϵ��";	
	cout<<"\t\t(4) �����ϵ��\n\n";
	cout<<"\t\t\t\t\t(5) �޸���ϵ��";
	cout<<"\t\t(6) ɾ����ϵ��\n\n";
	cout<<"\t\t\t\t\t(q) �˳�\n\n";
	cout<<"\n\t\t\t\t������ָ�����:";
}

void Initial(){
	Count=0;
	for(int i=0;i<TREENUM;i++) Root[i]=NULL;
	FileRead();
}

/////////////////////////////////////////////////////

void ShowALL(){  
	cout<<"\n\tͨѶ¼��Ϣ:\n\n";
	if(Root[NAME]==NULL or Count==0){
		cout<<"\t\t\tͨѶ¼Ϊ�գ�"<<endl; 
	}
	else{
		int cou = 1;
		cout<<"       ���   ����     �绰         QQ         ΢��           ����         סַ     ����       �ʱ�  �Ա�  ���\n\n";
		ShowTraversal(Root[0],cou);
	}
	cout<<"\n\n\n\t\t\t\t\t��������Ż�...";
	_getch();
} 

void Statistics(){
	ST1:
	cout<<"\n--ͨѶ¼ͳ�Ʋ�ѯ\n\n";
	cout<<"----��ϵ������: "<<Count<<endl<<endl; 
	cout<<"----����Ϣ��������:\n\n";
	for(int i=0;i<INFONUM-TREENUM;i++){
		cout<<"\t("<<i+1<<")"<<Str[i+TREENUM]<<" : "<<Class[i].size()<<endl; 
	}	
	cout<<"\n-----������Ҫ����ͳ�Ƶ���Ϣ���ͱ��(��q�˳�): " ;
	char x;
	do{
		x=_getch();
	} while((x<'1' or x>'5') and x!='q' and x!='Q');
	if(x=='q' or x=='Q'){
		return ;
	}
	else{
		system("cls");
		int ind = x-'1';
		cout<<"\n--ͨѶ¼ͳ�Ʋ�ѯ\n\n";
		cout<<"----��"<<Str[ind+TREENUM]<<"���Ͳ�ѯͳ��:\n\n";
		for(int i=0;i<Class[ind].size();i++){
			if(i%8==0) cout<<"     ";
			cout<<left<<setw(10)<<Class[ind][i]<<"  ";
			if((i+1)%8==0) cout<<endl;
		}
		string info;
		cout<<"\n\n----�������ѯ��Ϣ��q���أ�:";
		while(1){
			cin>>info;
			if(info=="q" or info=="Q"){
				system("cls");
				goto ST1;
			}
			if(find(Class[ind].begin(), Class[ind].end(), info) == Class[ind].end()){
				cout<<"----���������������:";
			}else break;
		}
		bool flag = Find(Root[0],ind+TREENUM,info);
		if(flag){
			cout<<"\n       ���   ����     �绰         QQ         ΢��           ����         סַ     ����       �ʱ�  �Ա�  ���\n\n";
			int cou=1;
			ShowSpecialTraversal(Root[NAME],cou,ind+TREENUM,info);
		}
		else{
			cout<<"---��Ϣ�ѱ�ɾ�����޸�"<<endl; // ������Ҳ���ܲ��˰� 
		}
	}
	cout<<"\n\n\n\t\t\t\t\t�����������...";
	_getch();
	system("cls");
	goto ST1;
} 

void FindMember(){
	FM1:
	cout<<"\n--��ϵ�˲�ѯ\n\n";
	Node* obj = NULL;
	char x = GetMember(obj);
	if(x=='q') return;
	if(x!='n'){
		system("cls");
		if(x=='r'){
			goto FM1;
		}
		else{ 
			cout<<"\n\n"; 
			cout<<"----��ϵ����Ϣ:\n\n";
			cout<<"\n         ����     �绰         QQ         ΢��           ����         סַ     ����       �ʱ�  �Ա�  ���\n\n";
			cout<<"\t";
			cout<<left<<setw(7)<<obj->information[0];
			cout<<left<<setw(13)<<obj->information[1];
			cout<<left<<setw(11)<<obj->information[2];
			cout<<left<<setw(12)<<obj->information[3];
			cout<<left<<setw(18)<<obj->information[4];
			cout<<left<<setw(8)<<obj->information[5];
			cout<<left<<setw(12)<<obj->information[6];
			cout<<left<<setw(8)<<obj->information[7];
			cout<<left<<setw(5)<<obj->information[8];
			cout<<left<<setw(6)<<obj->information[9];
			cout<<endl;
		}
	}
	cout<<"\n\n\n\t\t\t\t\t�����������...";
	_getch();
} 

void AddMember(){
	cout<<"\n--�����ϵ�� (����\"q\"ȡ�����)\n\n";
	string info[INFONUM];
	string tmp;
	for(int i=0;i<INFONUM;i++){
		cout<<"----��������ϵ�˵�"<<Str[i]<<":";
		cin>>tmp;
		if(tmp != "q") info[i]=tmp;
		else return; 
	}
	bool success = Insert(info);
	if(success){
		for(int j=0;j<INFONUM-TREENUM;j++){
			// ���������Ƿ��Ѿ����� 
			if(find(Class[j].begin(), Class[j].end(), info[j]) == Class[j].end()){
				Class[j].push_back(info[j+TREENUM]); 
			}
		}
		cout<<"--��ӳɹ���\n";
		Count++; // ����++ 
	}
	else{
		cout<<"--��Ϣ�ظ������ʧ�ܣ�\n";
	} 
	cout<<"\n\n\n\t\t\t\t\t�����������...";
	_getch();
} 

void ResMember(){
	RM1:
	cout<<"\n--�޸���ϵ����Ϣ\n\n";
	Node* obj = NULL;
	char x = GetMember(obj);
	if(x=='q') return;
	if(x!='n'){
		system("cls");
		if(x=='r'){
			goto RM1;
		}
		else{ 
			bool changed = false; // ����Ƿ��Ѿ����޸� 
			RM2:
			cout<<"\n--�޸���ϵ����Ϣ\n\n";
			cout<<"----��ϵ����Ϣ:\n";
			cout<<"\n         ����     �绰         QQ         ΢��           ����         סַ     ����       �ʱ�  �Ա�  ���\n\n";
			cout<<"\t";
			cout<<left<<setw(7)<<obj->information[0];
			cout<<left<<setw(13)<<obj->information[1];
			cout<<left<<setw(11)<<obj->information[2];
			cout<<left<<setw(12)<<obj->information[3];
			cout<<left<<setw(18)<<obj->information[4];
			cout<<left<<setw(8)<<obj->information[5];
			cout<<left<<setw(12)<<obj->information[6];
			cout<<left<<setw(8)<<obj->information[7];
			cout<<left<<setw(5)<<obj->information[8];
			cout<<left<<setw(6)<<obj->information[9];
			cout<<endl;
			cout<<"\n----��ѡ��Ҫ�޸ĵ���Ϣ:\n\n" ;
			for(int i=0;i<INFONUM;i++)
				cout<<"\t("<<i<<")"<<Str[i]<<endl;
			cout<<"\t(q)�����޸�\n";
			cout<<"\n----���������:" ;
			do{
				x=_getch();
			}while((x<'0' or x>'9') and x!='q' and x!='Q');
			int index = x-'0';
			if(x=='q' or x=='Q'){
				if(changed){  // �޸ķ�ʽ���� ɾ�� �� ���� ,����ֱ���޸ģ���Ϊ�漰��Ҫ���¹��� 
					string tmp[INFONUM] = obj->information;
					Remove(obj); 
					Insert(tmp);
				}
				return;
			}
			else{
				cout<<x<<endl;
				cout<<"----��������ϵ�˵�"<<Str[index]<<":";
				string info;
				cin>>info;
				if(info!=obj->information[index]){
					obj->information[index] = info;
					changed = true;
				}
				cout<<"----�޸ĳɹ���"<<endl; 
				Sleep(500);
				system("cls");
				goto RM2;
			}
		}
	}
	cout<<"\n\n\n\t\t\t\t\t�����������...";
	_getch();
} 

void DelMember(){
	DM1:
	cout<<"\n--ɾ����ϵ��\n\n";
	Node* obj = NULL;
	char x = GetMember(obj);
	if(x=='q') return;
	if(x!='n'){
		system("cls");
		if(x=='r'){
			goto DM1;
		}
		else{ 
			cout<<"\n--ɾ����ϵ��\n\n";
			cout<<"----��ϵ����Ϣ:\n";
			cout<<"\n         ����     �绰         QQ         ΢��           ����         סַ     ����       �ʱ�  �Ա�  ���\n\n";
			cout<<"\t";
			cout<<left<<setw(7)<<obj->information[0];
			cout<<left<<setw(13)<<obj->information[1];
			cout<<left<<setw(11)<<obj->information[2];
			cout<<left<<setw(12)<<obj->information[3];
			cout<<left<<setw(18)<<obj->information[4];
			cout<<left<<setw(8)<<obj->information[5];
			cout<<left<<setw(12)<<obj->information[6];
			cout<<left<<setw(8)<<obj->information[7];
			cout<<left<<setw(5)<<obj->information[8];
			cout<<left<<setw(6)<<obj->information[9];
			cout<<endl;
			cout<<"\n  ȷ��ɾ������Y/N��"<<endl;
			char y;
			do{
				y=_getch();
			}while(y!='Y' and y!='N');
			if(y == 'Y'){
				Remove(obj);
				Count--;
				cout<<"\n\n----ɾ���ɹ���"<<endl;
			}
			else{
				cout<<"\n\n----ȡ��ɾ��~"<<endl;
			}
		}
	} 
	cout<<"\n\n\n\t\t\t\t\t�����������...";
	_getch();	
} 

//////////////////////////////////////////////////////// 

/*
	����ֵ
	 q: �������˵�
	 n: ��ʾͨѶ¼Ϊ��
	 r: �ص���������ʼ��λ��ˢ�½���
	 ������1-5)����Ϊ���� 
*/ 
char GetMember(Node*&node){
	if(Root[NAME]==NULL or Count==0){
		cout<<"\t\t\tͨѶ¼Ϊ�գ�"<<endl;
		return 'n'; // ��ʾtree�� 
	}else{
		cout<<"----��ѡ���ѯ��ʽ:\n\n";
		for(int i=0;i<TREENUM;i++)
			cout<<"\t("<<i+1<<")"<<Str[i]<<endl;
		cout<<"\t(q)�������˵�\n\n";
		cout<<"----���������:";
		char x;
		do{
			x=_getch();
		}while((x<'1' or x>'5') and x!='q' and x!='Q');
		if(x=='q' or x=='Q') return 'q';
		else{
			cout<<x<<endl;
			system("cls");
			cout<<"\n--��ȡ��ϵ��\n\n";	 
			int index = x-'1';
			string info;
			cout<<"----��������ϵ�˵�"<<Str[index]<<"(���� q ����):";
			GM1:
			cin>>info;
			if(info=="q" or info=="Q"){
				return 'r'; // ��ʾ���»ص�������ʼλ�� 
			}else{
				node = search(info,Type(index));
				if(node==NULL){
					cout<<"------"<<Str[index]<<"������!����������:";
					goto GM1;
				}else{
					return x;// x ������Ϊ������������ 
				}
			} 
		}
	}
} 

void ShowTraversal(Node* node,int& cou){
	if(node!=NULL){
		cout<<"\t"<<left<<setw(5)<<cou;
		cout<<left<<setw(7)<<node->information[0];
		cout<<left<<setw(13)<<node->information[1];
		cout<<left<<setw(11)<<node->information[2];
		cout<<left<<setw(12)<<node->information[3];
		cout<<left<<setw(18)<<node->information[4];
		cout<<left<<setw(8)<<node->information[5];
		cout<<left<<setw(12)<<node->information[6];
		cout<<left<<setw(8)<<node->information[7];
		cout<<left<<setw(5)<<node->information[8];
		cout<<left<<setw(6)<<node->information[9];
		cout<<endl;
		if(node->left[NAME]) ShowTraversal(node->left[NAME],++cou);
		if(node->right[NAME]) ShowTraversal(node->right[NAME],++cou);
	}
} 

void ShowSpecialTraversal(Node* node,int& cou,const int& ind,const string& info){
	if(node!=NULL){
		if(node->information[ind]==info){
			cout<<"\t"<<left<<setw(5)<<cou;
			cout<<left<<setw(7)<<node->information[0];
			cout<<left<<setw(13)<<node->information[1];
			cout<<left<<setw(11)<<node->information[2];
			cout<<left<<setw(12)<<node->information[3];
			cout<<left<<setw(18)<<node->information[4];
			cout<<left<<setw(8)<<node->information[5];
			cout<<left<<setw(12)<<node->information[6];
			cout<<left<<setw(8)<<node->information[7];
			cout<<left<<setw(5)<<node->information[8];
			cout<<left<<setw(6)<<node->information[9];
			cout<<endl;
		}else{
			cou--;
		} 
		if(node->left[NAME]) ShowSpecialTraversal(node->left[NAME],++cou,ind,info);
		if(node->right[NAME]) ShowSpecialTraversal(node->right[NAME],++cou,ind,info);
	}
} 

void FileRead(){
	ifstream read("./information.txt",ios::in);
	int i=0;
	if(read){
		string info[INFONUM];
		while(read>>info[0]){ 
			for(int j=1;j<INFONUM;j++){
				read>>info[j];
				if(j>=TREENUM){
					// ���������Ƿ��Ѿ����� 
					if(find(Class[j-TREENUM].begin(), Class[j-TREENUM].end(), info[j]) == Class[j-TREENUM].end()){
						Class[j-TREENUM].push_back(info[j]); 
					}
				}
			}
			bool success = Insert(info);
			i++	;
			if(success) Count++; 
		}
		read.close();
	}
}

void FileWrite(){
	ofstream write("./information.txt",ios::out);
	if(write.is_open()){
		WriteTraversal(Root[0],write); 
		write.close();
	}
}

void WriteTraversal(Node* node,ofstream &write){
	if(write and node){
		for(int i=0;i<INFONUM;i++){
			write<<node->information[i]<<(i==INFONUM-1?"\n":"  ");
		}
		WriteTraversal(node->left[0],write);
		WriteTraversal(node->right[0],write);
	}
} 

void FreeSpace(Node* node){
	if(node){
		FreeSpace(node->left[0]);
		FreeSpace(node->right[0]);
		delete node;
	}
}

bool Find(Node* node,int ind,const string& info){
	if(node){
		if(node->information[ind]==info) return true;
		else return Find(node->left[0],ind,info) or Find(node->right[0],ind,info);
	}
	return false;
}
