#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <cmath>
using namespace std;

struct node{
    node(string n,int num,int s,long long p){
        name = n;
        number = num;
        sex = s;
        phone = p;
        next = NULL;
    }
    string name;
    int number;
    int sex;
    long long phone;
    node* next;
};

//同学信息：（性别和电话为虚构） 
long long Phone = 13100000000;
int Sex = 1;
node* Nodearr[80];
node* Hash[10];

int getSex(){
    Sex = (Sex+1)%2;
    return Sex;
}

long long getPhone(){
    Phone += 1;
    return Phone;
}

string Namearr[80] = {
    "zhangfangyuan","aihexuan","anjia","chaibin","chaozhizuo","zhengyang","zhengzheng","changfajin",
    "chencanhui","chenjianbin","chenxinde","chenshuo","chentailin","chentongfei","chenwangyong","chenweisong",
    "chenwenfeng","chenyang","chenyuzhen","chenzhixuan","dengjunkai","dongxuanyu","dongchenyu","fenjunxuan",
    "fenruinin","fenshangqin","gaodongyu","gaojinchuan","gaozheng","guyuran","guzhisan","guohairui",
    "guojiajun","guoxiao","guozhangxu","haiminghao","heshiyuan","hexu","heyinqi","heshanshan",
    "hongshang","huleirong","huangbaoyin","huangke","huangshanheng","huangshiming","huangxinyi","huangyifei",
    "huanglihui","huangzhiqi","huorundong","jiangneng","jinyanchen","kongwei","laiyujing","leixujia",
    "lifuxin","lichen","lijibang","lisaiwei","liwenhao","lixizhe","lixiuxiang","lizhixin",
    "lianzhefan","liangjinrong","liangsaibo","liangyanan","lianbgyuzha","liaojie","linguoliang","liupangqi",
    "liuhaoye","liujiahui","liulu","liurenhaotian","liuyuehua","luji","luyuyin","luyuxiao"
};

int Numberarr[80] = {
    17308211,17343001,17343002,17343003,17343004,17343005,17343006,17343007,
    17343008,17343009,17343010,17343011,17343012,17343013,17343014,17343015,
    17343016,17343017,17343018,17343020,17343022,17343023,17343024,17343025,
    17343026,17343027,17343028,17343029,17343030,17343031,17343032,17343033,
    17343034,17343035,17343036,17343037,17343038,17343039,17343040,17343041,
    17343042,17343043,17343044,17343045,17343046,17343047,17343048,17343049,
    17343050,17343051,17343052,17343053,17343054,17343055,17343056,17343057,
    17343058,17343060,17343061,17343062,17343063,17343064,17343065,17343066,
    17343067,17343068,17343069,17343070,17343071,17343072,17343073,17343074,
    17343075,17343076,17343077,17343078,17343079,17343080,17343081,17343082
};

void menu()//菜单 
{
    cout<<endl;
    cout<<"      menu:"<<endl;
    cout<<"      1: Show hash table"<<endl;
    cout<<"      2: Search people"<<endl;
    cout<<"      3: Insert people"<<endl;
    cout<<"      4: Delete people"<<endl;
    cout<<"      5: Exit"<<endl;
    cout<<endl;
}

void Show(){//展示函数： 
    cout<<endl;
    for(int i=0;i<10;i++){
        node* temp = Hash[i];
        cout<<"Hash["<<i<<"]: ";
        while(temp){
            cout<<temp->name;
            if(temp->next) cout<<" -> ";
            temp = temp->next;
        }
        cout<<endl;
    }
}

void Search(){//搜索函数： 
    cout<<endl;
    cout<<"Please input the student's name:"<<endl;
    string s;
    cin>>s;
    int n = (s[0] + s[s.length()-1])%10;
    node* temp = Hash[n];
    int count = 1; 
    while(temp and temp->name != s) {
    	temp = temp->next;
    	count++;
	}
    if(temp == NULL) {
    	cout<<"Not Exist!"<<endl;
    	count--;
	}
    else {
        cout<<"     Student's name: "<<temp->name<<endl;
        cout<<"     Student's ID: "<<temp->number<<endl;
        cout<<"     Student's sex: "<<(temp->sex?"boy":"girl")<<endl;
        cout<<"     Student's phone: "<<temp->phone<<endl;
    }
    cout<<"     count time = "<<count<<endl;
}

void Insert(){//插入函数： 
    cout<<endl;
    string s;
    int id,sex;
    long long p;
    cout<<"Please input the student's name:"<<endl;
    cin>>s;
    cout<<"Please input the student's ID:"<<endl;
    cin>>id;
    cout<<"Please input the student's sex(0 for girl and 1 for boy):"<<endl;
    cin>>sex;
    cout<<"Please input the student's phone:"<<endl;
    cin>>p;
    node* ptr = new node(s,id,sex,p);
	int n = (s[0] + s[s.length()-1])%10;
    node* temp = Hash[n];
    while(temp->next) {
        if(temp->name != s) temp = temp->next;
        else{
            cout<<"Duplicate information! Insert failed!"<<endl;
            return;
        }
    }
    if(temp->name != s){}
    else{
        cout<<"Duplicate information! Insert failed!"<<endl;
        return;
    }
    temp->next = ptr;
    cout<<"Insert success!"<<endl;
}

void Delete(){//删除函数： 
    string s;
    cout<<"Please input the student's name:"<<endl;
    cin>>s;
    int n = (s[0] + s[s.length()-1])%10;
    node* temp = Hash[n];
    node* temp2 = temp->next;
    if(temp->name == s){
        delete temp;
        Hash[n] = temp2;
        cout<<"Delete successful!"<<endl;
        return;
    }
    while(temp2) {
        if(temp2->name != s) {
            temp = temp->next;
            temp2 = temp2->next;
        }
        else{
            temp->next = temp2->next;
            delete temp2;
            cout<<"Delete successful!"<<endl;
            return;
        }
    }
    cout<<"Not exist! Delete failed!"<<endl;
}

int main()
{
    int i,j;
    string c;
    //开始构造基本的哈希表： 
    for(i=0;i<80;i++) Nodearr[i] = new node(Namearr[i],Numberarr[i],getSex(),getPhone());
    for(i=0;i<10;i++) Hash[i] = NULL;
    for(i=0;i<80;i++){
        int n = (Nodearr[i]->name[0] + Nodearr[i]->name[Nodearr[i]->name.length()-1])%10;
        if(Hash[n] == NULL){
            Hash[n] = Nodearr[i];
        }
        else{
            node* temp = Hash[n];
            while(temp->next) temp = temp->next;
            temp->next = Nodearr[i];
        }
    }
    //构造结束 
    th:
    menu();
    cin>>c;
    if(c == "1") {
        Show();
        goto th;
    }
    else if(c == "2") {
        Search();
        goto th;
    }
    else if(c == "3") {
        Insert();
        goto th;
    }
    else if(c == "4") {
        Delete();
        goto th;
    }
}
