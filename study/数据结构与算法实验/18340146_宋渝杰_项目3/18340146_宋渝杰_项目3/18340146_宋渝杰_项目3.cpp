#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <windows.h>
#include <iomanip>
#include <conio.h> 
using namespace std;

void Menu() // 菜单栏 
{
	cout << "\n";
	cout << "\t\t\t\t\t  ----------------------------" << endl;
	cout << "\t\t\t\t\t\t  |族  ※  谱|" << endl;
	cout << "\t\t\t\t\t  ----------------------------" << endl;
	cout << "\n\n\n";
	cout << "\t\t\t\t\t(1) 添加";
	cout << "\t\t(2) 删除\n\n";
	cout << "\t\t\t\t\t(3) 查询";
	cout << "\t\t(4) 统计\n\n";
	cout << "\t\t\t\t\t(5) 打印";
	cout << "\t\t(6) 结束程序\n\n";
	cout << "\n\t\t\t\t请输入指令(输入序号):";
}

struct Node { // 树节点 
	Node() {	}
	Node(string a, bool b, int c, int d, int e, int f, Node* g, Node* h, Node* i, Node* j) {
		name = a;
		isMan = b;
		age = c;
		date_of_birth = d;
		date_of_death = e;
		generation = f;
		father = g;
		old_brother = h;
		young_brother = i;
		son = j;
	}//构造函数 
	string name;
	bool isMan;//1为男，0为女 
	int age; //若死了则为死时的年龄 
	int date_of_birth;
	int date_of_death; //死亡日期，-1还活着  
	int generation; //辈分 
	Node* father;
	Node* old_brother;
	Node* young_brother;
	Node* son;
};


class Tree {
public:
	Node* root;
	Tree();
	Tree(Node* r);
	void Insert();
	void Delete(string x);
	Node* Find(Node* p, string find);
	void Search(Node* p, string find);
	void Statistics(vector<Node*>& vec);
	void Display();
};

void max_generation(Node *p,int& max){ // 获取最大辈分 
	if(p==NULL) return;
	if(p->generation > max)  max = p->generation;
	max_generation(p->son,max);
	max_generation(p->young_brother,max);
}

void preorder(Node* p, string s) { // 先序遍历输出直观树 
	if (p == NULL) return;
	if (p->generation == 1) cout << left << setw(5) << p->name << endl;
	else if (p->young_brother == NULL)  cout << s << "┗-------" << left << setw(5) << p->name << endl;
	else cout << s << "├-------" << left << setw(5) << p->name << endl;
	Node* son = p->son;
	while (son != NULL) {
		if (p->generation == 1) {
			preorder(son, s);
		}
		else {
			if (p->young_brother != NULL) {
				preorder(son, s + "┃\t");
			}
			else {
				preorder(son, s + "\t");
			}
		}
		son = son->young_brother;
	}
}


Tree::Tree() {
	root = new Node();
	root->name = "艾莉";
	root->age = 58;
	root->date_of_birth = 1842;
	root->date_of_death = 1900;
	root->father = NULL;
	root->generation = 1;
	root->isMan = 0;
	root->son = NULL;
	root->old_brother = NULL;
	root->young_brother = NULL;
}

Tree::Tree(Node* r)
{
	root = new Node();
	root->name = r->name;
	root->age = r->age;
	root->date_of_birth = r->date_of_birth;
	root->date_of_death = r->date_of_death;
	root->father = r->father;
	root->generation = r->generation;
	root->isMan = r->isMan;
	root->son = r->son;
	root->old_brother = r->old_brother;
	root->young_brother = r->young_brother;
}

void Tree::Insert() // 插入函数 
{
	string x, y;
	int a, b, c, d;

	cout << "输入要插入的子女的上一辈的姓名：";
	cin >> x;
	Node* p = Find(root, x); //看看这个人在不在现有的族谱里 
	Node* q = new Node();
	while (p == NULL)
	{
		cout << "此人不存在，请重新输入：";
		cin >> x;
		p = Find(root, x);
	}


	cout << "输入要插入的子女的姓名：";
	cin >> y;
	Node* m = Find(root, y);
	while (m != NULL) //有重名的情况 
	{
		cout << "出现重名，请重新输入：";
		cin >> y;
		m = Find(root, y);
	}


	cout << "此子女的性别（1为男，0为女）：";
	cin >> a;
	while (!cin.good()) {
		cout << "性别输入错误哦，1为男，2为女，请重新输入：" << endl;
		cin.clear();
		cin.sync();
		cin >> a;
	}//判断如果a不是int类型，报错，并重新输入   
	while (a != 1 && a != 0)
	{
		cout << "性别输入错误哦，1为男，2为女，请重新输入：";
		cin >> a;
	}


	cout << "此子女年龄（若去世了则为去世时的年龄）：";
	cin >> b;
	while (!cin.good()) {
		cout << "年龄输入错误,请重新输入：" << endl;
		cin.clear();
		cin.sync();
		cin >> b;
	}//判断如果b不是int类型，报错，并重新输入   


	cout << "此子女出生年份：";
	cin >> c;
	while (!cin.good()) {
		cout << "出生年份输入错误，请重新输入：" << endl;
		cin.clear();
		cin.sync();
		cin >> c;
	}//判断如果不是int类型，报错，并重新输入  


	cout << "此子女死亡年份(若还活着则输入-1)：";
	cin >> d;
	while (!cin.good()) {
		cout << "死亡年份输入错误，请重新输入：" << endl;
		cin.clear();
		cin.sync();
		cin >> c;
	}//判断如果不是int类型，报错，并重新输入   


	q->name = y;
	q->generation = p->generation + 1;
	q->age = b;
	q->date_of_birth = c;
	q->date_of_death = d;
	q->isMan = a;
	q->son = NULL;
	q->young_brother = NULL;
	q->father = p;
	if (p->son == NULL) {
		p->son = q;
		q->old_brother = NULL;
	}
	else {
		Node* o = p->son;		// 这里按照出生日期排序 
		while (o->young_brother != NULL and o->young_brother->date_of_birth < q->date_of_birth)
			o = o->young_brother;
		if(o->date_of_birth > q->date_of_birth){
			q->old_brother = NULL;
			q->young_brother = o;
			o->old_brother = q;
			o->father->son = q;
		}
		else if(o->young_brother != NULL){
			q->young_brother = o->young_brother;
			o->young_brother->old_brother = q;	
			o->young_brother = q;
			q->old_brother = o;
		}
		else{
			o->young_brother = q;
			q->old_brother = o;
		}
	}
	cout << "添加成功！" << endl;
}



void Tree::Delete(string x) //把x移出家谱 
{
	if (x == "艾莉") {
		cout << "???祖宗删不得!!!" << endl;
		cout << "您的操作被拒绝" << endl;
		return;
	}
	Node* p = Find(root, x);
	if (p == NULL)
	{
		cout << "家谱中不存在这个人" << endl;
		return;
	}
	Node* q = p;
	if (p->father->son == p) {
		q = p->young_brother;
		p->father->son = q;
		q->old_brother = NULL;
		//delete(new)
		delete p;
	}
	else {
		if (p->young_brother != NULL) {
			q = p->young_brother;
			p->old_brother->young_brother = q;
			q->old_brother = p->old_brother;
		}
		else {
			p->old_brother->young_brother = NULL;
		}
		//delete(new)
		delete p;
	}
	cout << "删除成功！" << endl;
}



Node* Tree::Find(Node* p, string find) // 在族谱中找到名字为find的这个人 
{
	Node* q = NULL;
	if (!p)
		return NULL;
	if (p->name == find)
		return p;
	if (p->young_brother)
	{
		q = Find(p->young_brother, find);
		if (q != NULL)
			return q;
	}
	if (p->son)
	{
		q = Find(p->son, find);
		if (q != NULL)
			return q;
	}
	return NULL;
}


void Tree::Search(Node* p, string find) // 查询函数 
{
	Node* q = Find(p, find);
	if (q == NULL)
	{
		cout << "不存在这个人" << endl;
		return;
	}
	cout << q->name << "的个人信息：" << endl;
	cout << "年龄： " << q->age << endl;
	//data of birth and death
	cout << "生卒： " << q->date_of_birth << "-";
	if (q->date_of_death == -1) cout << "????" << endl;
	else cout << q->date_of_death << endl;
	//generation 
	cout << "辈分： " << "第" << q->generation << "代" << endl;
	//sex 
	cout << "性别： ";
	if (q->isMan == 1)  cout << "男" << endl;
	else cout << "女" << endl;
	//father 
	if (q->father == NULL) cout << "父代不详" << endl;
	else {
		if (q->father->isMan)  cout << "父亲： " << q->father->name << endl;
		else cout << "母亲： " << q->father->name << endl;
	}
	//brother
	if (q->old_brother == NULL && q->young_brother == NULL) {
		cout << "没有兄弟姐妹" << endl;
	}
	else {
		cout << "兄弟姐妹： ";
		stack<string> s1;
		p = q;
		while (p->old_brother) {
			p = p->old_brother;
			s1.push(p->name);
		}
		while (!s1.empty()) {
			cout << s1.top() << "  ";
			s1.pop();
		}
		p = q;
		while (p->young_brother) {
			p = p->young_brother;
			cout << p->name << "  ";
		}
		cout << endl;
	}
	//son
	p = q->son;
	if (p == NULL) {
		cout << "没有孩子" << endl;
	}
	else {
		cout << "孩子： ";
		while (p) {
			cout << p->name << "  ";
			p = p->young_brother;
		}
		cout << endl;
	}
}

void Tree::Statistics(vector<Node*>& vec) // 统计函数 
{
	vec.push_back(root);
	int max = 0; 
	for (int i = 0; i < vec.size(); i++) {
		if (vec[i]->son != NULL) vec.push_back(vec[i]->son);
		if (vec[i]->young_brother != NULL)vec.push_back(vec[i]->young_brother);
	}
	for (int j = 0; j < vec.size(); j++) {
		if(vec[j]->generation > max) max = vec[j]->generation;
	}
	cout << "  	   辈分		      姓名	   性别	      生卒	        父代		" << endl;
	for (int i = 1; i <= max; i++) {
		for (int j = 0; j < vec.size(); j++) {
			if (vec[j]->generation == i) {
				Node* p = vec[j];
				cout << "	  第" << right << setw(2) << p->generation << " 代	       " << left << setw(12) << p->name;
				if (p->isMan) cout << "男	  ";
				else cout << "女	  ";
				cout << right << setw(5) << p->date_of_birth << "-";
				if (p->date_of_death == -1)  cout << "?		";
				else cout << left << setw(5) << p->date_of_death << "		";
				if (p->father == NULL) cout << "不详" << endl;
				else cout << left << setw(12) << p->father->name << endl;
			}
		}
	}
}

void Tree::Display() { // 显示直观树函数 
	int max=0;
	Node* p = root;
	int n;
	cout << endl << "\t\t\t\t\t-----------------\t\t\t\t\t" << endl;
	cout << "\t\t\t\t\t      族 谱      \t\t\t\t\t" << endl;
	cout << "\t\t\t\t\t-----------------\t\t\t\t\t" << endl << endl;
	max_generation(root,max);
	int i;
	for(i=1;i<max;i++){
		cout << i << "代     " ; 
	}
	cout << i <<"代" <<endl;
	preorder(root, "");
}

int main()
{
	// 初始化一个族谱 
	Tree t;
	Node* shanshan = new Node("姗姗", 0, 80, 1860, 1940, 2, t.root, NULL, NULL, NULL);
	Node* wenyan = new Node("文彦", 1, 69, 1864, 1933, 2, t.root, shanshan, NULL, NULL);
	Node* shixian = new Node("世贤", 1, 63, 1866, 1929, 2, t.root, wenyan, NULL, NULL);
	Node* pinru = new Node("品如", 0, 75, 1880, 1955, 3, shanshan, NULL, NULL, NULL);
	Node* xiaxue = new Node("夏雪", 0, 100, 1900, -1, 4, pinru, NULL, NULL, NULL);
	Node* xiatian = new Node("夏天", 1, 94, 1904, -1, 4, pinru, xiaxue, NULL, NULL);
	Node* xiayu = new Node("夏雨", 1, 85, 1915, -1, 4, pinru, xiayu, NULL, NULL);
	Node* gaoshou = new Node("高手", 1, 82, 1884, 1966, 3, wenyan, NULL, NULL, NULL);
	Node* gaoren = new Node("高人", 1, 92, 1888, 1980, 3, wenyan, gaoshou, NULL, NULL);
	Node* daer = new Node("洪大儿", 1, 72, 1888, 1960, 3, shixian, NULL, NULL, NULL);
	Node* xiaoren = new Node("洪小人", 0, 87, 1890, 1977, 3, shixian, daer, NULL, NULL);
	t.root->son = shanshan;
	shanshan->young_brother = wenyan;
	wenyan->young_brother = shixian;
	daer->young_brother = xiaoren;
	gaoshou->young_brother = gaoren;
	xiaxue->young_brother = xiatian;
	xiatian->young_brother = xiayu;
	shixian->son = daer;
	wenyan->son = gaoshou;
	shanshan->son = pinru;
	pinru->son = xiaxue;
	
	int x;
	string a;
	while (true)
	{
		Menu();
		cin >> x;
		if (!cin.good()) {
			cout << "输入错误，请重新输入" << endl;
			cin.clear();
			cin.sync();
			Sleep(500);
			system("cls");
			continue;
		}//判断如果x不是int类型，报错，并重新输入 
		system("cls");
		vector<Node*> vec;
		switch (x) {
		case 1:
			t.Insert();
			break;
		case 2:
			cout << "输入你要把ta从家谱中移除的人的名字：";
			cin >> a;
			t.Delete(a);
			break;
		case 3:
			cout << "输入你想获取信息的人的名字：";
			cin >> a;
			t.Search(t.root, a);
			break;
		case 4:
			t.Statistics(vec);
			break;
		case 5:
			t.Display();
			break;
		case 6:
			cout << "对家谱操作结束，最终家谱显示为：" << endl;
			t.Display();
			break;
		default:
			cout << "输入错误，请重新输入" << endl;
			break;
		}
		if (x == 6) break;
		cout << "\n\t\t\t按任意键返回...";
		_getch();
		system("cls");
	}
	return 0;
}

