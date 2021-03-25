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

const string Str[INFONUM] = {"名字","电话号码","QQ","微信","邮箱","地址","生日","邮编","性别","类别"}; 
Node* Root[TREENUM];
int Count;  // 通讯录中记录的人数  
vector<string> Class[INFONUM-TREENUM]; // 用于分类查找 

void Menu(); 		// 输出主菜单 
void Initial(); 	// 程序启动的初始化操作 
void ShowALL(); 	// 显示所有人信息
void FindMember();	//查找显示对象 
void AddMember();	//添加对象  
void ResMember();	//修改对象 
void DelMember();	//删除对象 
void Statistics(); // 统计通讯录信息 

// 辅助函数，用于实现特定功能 
char GetMember(Node*&node);	//将多个函数的共同部分独立成函数，减少代码量 
void ShowSpecialTraversal(Node* node,int& cou,const int& ind,const string& info); // 筛选显示 
void ShowTraversal(Node* node,int& cou); //// 遍历树将信息输出显示 
void WriteTraversal(Node* node,ofstream&out); // 遍历树将信息写入文件 
void FileRead(); 	// 读取文件信息 
void FileWrite();	// 修改并关闭文件 
void FreeSpace(Node* node);// 释放空间 
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
	cout<<"\t\t\t\t\t | 个     人     通     讯     录 |"<<endl;
	cout<<"\t\t\t\t\t------------------------------------"<<endl;
	cout<<"\n\n\n";
	cout<<"\t\t\t\t\t(1) 查看全部信息";	
	cout<<"\t(2) 通讯录统计查询\n\n";	
	cout<<"\t\t\t\t\t(3) 查询联系人";	
	cout<<"\t\t(4) 添加联系人\n\n";
	cout<<"\t\t\t\t\t(5) 修改联系人";
	cout<<"\t\t(6) 删除联系人\n\n";
	cout<<"\t\t\t\t\t(q) 退出\n\n";
	cout<<"\n\t\t\t\t请输入指令序号:";
}

void Initial(){
	Count=0;
	for(int i=0;i<TREENUM;i++) Root[i]=NULL;
	FileRead();
}

/////////////////////////////////////////////////////

void ShowALL(){  
	cout<<"\n\t通讯录信息:\n\n";
	if(Root[NAME]==NULL or Count==0){
		cout<<"\t\t\t通讯录为空！"<<endl; 
	}
	else{
		int cou = 1;
		cout<<"       序号   姓名     电话         QQ         微信           邮箱         住址     生日       邮编  性别  类别\n\n";
		ShowTraversal(Root[0],cou);
	}
	cout<<"\n\n\n\t\t\t\t\t按任意键放回...";
	_getch();
} 

void Statistics(){
	ST1:
	cout<<"\n--通讯录统计查询\n\n";
	cout<<"----联系人数量: "<<Count<<endl<<endl; 
	cout<<"----各信息类型数量:\n\n";
	for(int i=0;i<INFONUM-TREENUM;i++){
		cout<<"\t("<<i+1<<")"<<Str[i+TREENUM]<<" : "<<Class[i].size()<<endl; 
	}	
	cout<<"\n-----输入需要进行统计的信息类型编号(按q退出): " ;
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
		cout<<"\n--通讯录统计查询\n\n";
		cout<<"----按"<<Str[ind+TREENUM]<<"类型查询统计:\n\n";
		for(int i=0;i<Class[ind].size();i++){
			if(i%8==0) cout<<"     ";
			cout<<left<<setw(10)<<Class[ind][i]<<"  ";
			if((i+1)%8==0) cout<<endl;
		}
		string info;
		cout<<"\n\n----请输入查询信息（q返回）:";
		while(1){
			cin>>info;
			if(info=="q" or info=="Q"){
				system("cls");
				goto ST1;
			}
			if(find(Class[ind].begin(), Class[ind].end(), info) == Class[ind].end()){
				cout<<"----输入错误，重新输入:";
			}else break;
		}
		bool flag = Find(Root[0],ind+TREENUM,info);
		if(flag){
			cout<<"\n       序号   姓名     电话         QQ         微信           邮箱         住址     生日       邮编  性别  类别\n\n";
			int cou=1;
			ShowSpecialTraversal(Root[NAME],cou,ind+TREENUM,info);
		}
		else{
			cout<<"---信息已被删除或修改"<<endl; // 两下子也接受不了吧 
		}
	}
	cout<<"\n\n\n\t\t\t\t\t按任意键返回...";
	_getch();
	system("cls");
	goto ST1;
} 

void FindMember(){
	FM1:
	cout<<"\n--联系人查询\n\n";
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
			cout<<"----联系人信息:\n\n";
			cout<<"\n         姓名     电话         QQ         微信           邮箱         住址     生日       邮编  性别  类别\n\n";
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
	cout<<"\n\n\n\t\t\t\t\t按任意键返回...";
	_getch();
} 

void AddMember(){
	cout<<"\n--添加联系人 (输入\"q\"取消添加)\n\n";
	string info[INFONUM];
	string tmp;
	for(int i=0;i<INFONUM;i++){
		cout<<"----请输入联系人的"<<Str[i]<<":";
		cin>>tmp;
		if(tmp != "q") info[i]=tmp;
		else return; 
	}
	bool success = Insert(info);
	if(success){
		for(int j=0;j<INFONUM-TREENUM;j++){
			// 查找类型是否已经存在 
			if(find(Class[j].begin(), Class[j].end(), info[j]) == Class[j].end()){
				Class[j].push_back(info[j+TREENUM]); 
			}
		}
		cout<<"--添加成功！\n";
		Count++; // 数量++ 
	}
	else{
		cout<<"--信息重复，添加失败！\n";
	} 
	cout<<"\n\n\n\t\t\t\t\t按任意键返回...";
	_getch();
} 

void ResMember(){
	RM1:
	cout<<"\n--修改联系人信息\n\n";
	Node* obj = NULL;
	char x = GetMember(obj);
	if(x=='q') return;
	if(x!='n'){
		system("cls");
		if(x=='r'){
			goto RM1;
		}
		else{ 
			bool changed = false; // 标记是否已经有修改 
			RM2:
			cout<<"\n--修改联系人信息\n\n";
			cout<<"----联系人信息:\n";
			cout<<"\n         姓名     电话         QQ         微信           邮箱         住址     生日       邮编  性别  类别\n\n";
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
			cout<<"\n----请选择要修改的信息:\n\n" ;
			for(int i=0;i<INFONUM;i++)
				cout<<"\t("<<i<<")"<<Str[i]<<endl;
			cout<<"\t(q)结束修改\n";
			cout<<"\n----请输入序号:" ;
			do{
				x=_getch();
			}while((x<'0' or x>'9') and x!='q' and x!='Q');
			int index = x-'0';
			if(x=='q' or x=='Q'){
				if(changed){  // 修改方式是先 删除 再 插入 ,不能直接修改，因为涉及树要重新构造 
					string tmp[INFONUM] = obj->information;
					Remove(obj); 
					Insert(tmp);
				}
				return;
			}
			else{
				cout<<x<<endl;
				cout<<"----请输入联系人的"<<Str[index]<<":";
				string info;
				cin>>info;
				if(info!=obj->information[index]){
					obj->information[index] = info;
					changed = true;
				}
				cout<<"----修改成功！"<<endl; 
				Sleep(500);
				system("cls");
				goto RM2;
			}
		}
	}
	cout<<"\n\n\n\t\t\t\t\t按任意键返回...";
	_getch();
} 

void DelMember(){
	DM1:
	cout<<"\n--删除联系人\n\n";
	Node* obj = NULL;
	char x = GetMember(obj);
	if(x=='q') return;
	if(x!='n'){
		system("cls");
		if(x=='r'){
			goto DM1;
		}
		else{ 
			cout<<"\n--删除联系人\n\n";
			cout<<"----联系人信息:\n";
			cout<<"\n         姓名     电话         QQ         微信           邮箱         住址     生日       邮编  性别  类别\n\n";
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
			cout<<"\n  确定删除？（Y/N）"<<endl;
			char y;
			do{
				y=_getch();
			}while(y!='Y' and y!='N');
			if(y == 'Y'){
				Remove(obj);
				Count--;
				cout<<"\n\n----删除成功！"<<endl;
			}
			else{
				cout<<"\n\n----取消删除~"<<endl;
			}
		}
	} 
	cout<<"\n\n\n\t\t\t\t\t按任意键返回...";
	_getch();	
} 

//////////////////////////////////////////////////////// 

/*
	返回值
	 q: 返回主菜单
	 n: 表示通讯录为空
	 r: 回到函数的起始部位（刷新界面
	 其他（1-5)：作为索引 
*/ 
char GetMember(Node*&node){
	if(Root[NAME]==NULL or Count==0){
		cout<<"\t\t\t通讯录为空！"<<endl;
		return 'n'; // 表示tree空 
	}else{
		cout<<"----请选择查询方式:\n\n";
		for(int i=0;i<TREENUM;i++)
			cout<<"\t("<<i+1<<")"<<Str[i]<<endl;
		cout<<"\t(q)返回主菜单\n\n";
		cout<<"----请输入序号:";
		char x;
		do{
			x=_getch();
		}while((x<'1' or x>'5') and x!='q' and x!='Q');
		if(x=='q' or x=='Q') return 'q';
		else{
			cout<<x<<endl;
			system("cls");
			cout<<"\n--获取联系人\n\n";	 
			int index = x-'1';
			string info;
			cout<<"----请输入联系人的"<<Str[index]<<"(输入 q 返回):";
			GM1:
			cin>>info;
			if(info=="q" or info=="Q"){
				return 'r'; // 表示重新回到函数开始位置 
			}else{
				node = search(info,Type(index));
				if(node==NULL){
					cout<<"------"<<Str[index]<<"不存在!请重新输入:";
					goto GM1;
				}else{
					return x;// x 可能作为后面程序的索引 
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
					// 查找类型是否已经存在 
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
