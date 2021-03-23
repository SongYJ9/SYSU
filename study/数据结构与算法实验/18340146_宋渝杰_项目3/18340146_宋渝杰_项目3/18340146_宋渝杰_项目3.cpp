#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <windows.h>
#include <iomanip>
#include <conio.h> 
using namespace std;

void Menu() // �˵��� 
{
	cout << "\n";
	cout << "\t\t\t\t\t  ----------------------------" << endl;
	cout << "\t\t\t\t\t\t  |��  ��  ��|" << endl;
	cout << "\t\t\t\t\t  ----------------------------" << endl;
	cout << "\n\n\n";
	cout << "\t\t\t\t\t(1) ���";
	cout << "\t\t(2) ɾ��\n\n";
	cout << "\t\t\t\t\t(3) ��ѯ";
	cout << "\t\t(4) ͳ��\n\n";
	cout << "\t\t\t\t\t(5) ��ӡ";
	cout << "\t\t(6) ��������\n\n";
	cout << "\n\t\t\t\t������ָ��(�������):";
}

struct Node { // ���ڵ� 
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
	}//���캯�� 
	string name;
	bool isMan;//1Ϊ�У�0ΪŮ 
	int age; //��������Ϊ��ʱ������ 
	int date_of_birth;
	int date_of_death; //�������ڣ�-1������  
	int generation; //���� 
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

void max_generation(Node *p,int& max){ // ��ȡ��󱲷� 
	if(p==NULL) return;
	if(p->generation > max)  max = p->generation;
	max_generation(p->son,max);
	max_generation(p->young_brother,max);
}

void preorder(Node* p, string s) { // ����������ֱ���� 
	if (p == NULL) return;
	if (p->generation == 1) cout << left << setw(5) << p->name << endl;
	else if (p->young_brother == NULL)  cout << s << "��-------" << left << setw(5) << p->name << endl;
	else cout << s << "��-------" << left << setw(5) << p->name << endl;
	Node* son = p->son;
	while (son != NULL) {
		if (p->generation == 1) {
			preorder(son, s);
		}
		else {
			if (p->young_brother != NULL) {
				preorder(son, s + "��\t");
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
	root->name = "����";
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

void Tree::Insert() // ���뺯�� 
{
	string x, y;
	int a, b, c, d;

	cout << "����Ҫ�������Ů����һ����������";
	cin >> x;
	Node* p = Find(root, x); //����������ڲ������е������� 
	Node* q = new Node();
	while (p == NULL)
	{
		cout << "���˲����ڣ����������룺";
		cin >> x;
		p = Find(root, x);
	}


	cout << "����Ҫ�������Ů��������";
	cin >> y;
	Node* m = Find(root, y);
	while (m != NULL) //����������� 
	{
		cout << "�������������������룺";
		cin >> y;
		m = Find(root, y);
	}


	cout << "����Ů���Ա�1Ϊ�У�0ΪŮ����";
	cin >> a;
	while (!cin.good()) {
		cout << "�Ա��������Ŷ��1Ϊ�У�2ΪŮ�����������룺" << endl;
		cin.clear();
		cin.sync();
		cin >> a;
	}//�ж����a����int���ͣ���������������   
	while (a != 1 && a != 0)
	{
		cout << "�Ա��������Ŷ��1Ϊ�У�2ΪŮ�����������룺";
		cin >> a;
	}


	cout << "����Ů���䣨��ȥ������Ϊȥ��ʱ�����䣩��";
	cin >> b;
	while (!cin.good()) {
		cout << "�����������,���������룺" << endl;
		cin.clear();
		cin.sync();
		cin >> b;
	}//�ж����b����int���ͣ���������������   


	cout << "����Ů������ݣ�";
	cin >> c;
	while (!cin.good()) {
		cout << "�����������������������룺" << endl;
		cin.clear();
		cin.sync();
		cin >> c;
	}//�ж��������int���ͣ���������������  


	cout << "����Ů�������(��������������-1)��";
	cin >> d;
	while (!cin.good()) {
		cout << "�����������������������룺" << endl;
		cin.clear();
		cin.sync();
		cin >> c;
	}//�ж��������int���ͣ���������������   


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
		Node* o = p->son;		// ���ﰴ�ճ����������� 
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
	cout << "��ӳɹ���" << endl;
}



void Tree::Delete(string x) //��x�Ƴ����� 
{
	if (x == "����") {
		cout << "???����ɾ����!!!" << endl;
		cout << "���Ĳ������ܾ�" << endl;
		return;
	}
	Node* p = Find(root, x);
	if (p == NULL)
	{
		cout << "�����в����������" << endl;
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
	cout << "ɾ���ɹ���" << endl;
}



Node* Tree::Find(Node* p, string find) // ���������ҵ�����Ϊfind������� 
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


void Tree::Search(Node* p, string find) // ��ѯ���� 
{
	Node* q = Find(p, find);
	if (q == NULL)
	{
		cout << "�����������" << endl;
		return;
	}
	cout << q->name << "�ĸ�����Ϣ��" << endl;
	cout << "���䣺 " << q->age << endl;
	//data of birth and death
	cout << "���䣺 " << q->date_of_birth << "-";
	if (q->date_of_death == -1) cout << "????" << endl;
	else cout << q->date_of_death << endl;
	//generation 
	cout << "���֣� " << "��" << q->generation << "��" << endl;
	//sex 
	cout << "�Ա� ";
	if (q->isMan == 1)  cout << "��" << endl;
	else cout << "Ů" << endl;
	//father 
	if (q->father == NULL) cout << "��������" << endl;
	else {
		if (q->father->isMan)  cout << "���ף� " << q->father->name << endl;
		else cout << "ĸ�ף� " << q->father->name << endl;
	}
	//brother
	if (q->old_brother == NULL && q->young_brother == NULL) {
		cout << "û���ֵܽ���" << endl;
	}
	else {
		cout << "�ֵܽ��ã� ";
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
		cout << "û�к���" << endl;
	}
	else {
		cout << "���ӣ� ";
		while (p) {
			cout << p->name << "  ";
			p = p->young_brother;
		}
		cout << endl;
	}
}

void Tree::Statistics(vector<Node*>& vec) // ͳ�ƺ��� 
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
	cout << "  	   ����		      ����	   �Ա�	      ����	        ����		" << endl;
	for (int i = 1; i <= max; i++) {
		for (int j = 0; j < vec.size(); j++) {
			if (vec[j]->generation == i) {
				Node* p = vec[j];
				cout << "	  ��" << right << setw(2) << p->generation << " ��	       " << left << setw(12) << p->name;
				if (p->isMan) cout << "��	  ";
				else cout << "Ů	  ";
				cout << right << setw(5) << p->date_of_birth << "-";
				if (p->date_of_death == -1)  cout << "?		";
				else cout << left << setw(5) << p->date_of_death << "		";
				if (p->father == NULL) cout << "����" << endl;
				else cout << left << setw(12) << p->father->name << endl;
			}
		}
	}
}

void Tree::Display() { // ��ʾֱ�������� 
	int max=0;
	Node* p = root;
	int n;
	cout << endl << "\t\t\t\t\t-----------------\t\t\t\t\t" << endl;
	cout << "\t\t\t\t\t      �� ��      \t\t\t\t\t" << endl;
	cout << "\t\t\t\t\t-----------------\t\t\t\t\t" << endl << endl;
	max_generation(root,max);
	int i;
	for(i=1;i<max;i++){
		cout << i << "��     " ; 
	}
	cout << i <<"��" <<endl;
	preorder(root, "");
}

int main()
{
	// ��ʼ��һ������ 
	Tree t;
	Node* shanshan = new Node("��", 0, 80, 1860, 1940, 2, t.root, NULL, NULL, NULL);
	Node* wenyan = new Node("����", 1, 69, 1864, 1933, 2, t.root, shanshan, NULL, NULL);
	Node* shixian = new Node("����", 1, 63, 1866, 1929, 2, t.root, wenyan, NULL, NULL);
	Node* pinru = new Node("Ʒ��", 0, 75, 1880, 1955, 3, shanshan, NULL, NULL, NULL);
	Node* xiaxue = new Node("��ѩ", 0, 100, 1900, -1, 4, pinru, NULL, NULL, NULL);
	Node* xiatian = new Node("����", 1, 94, 1904, -1, 4, pinru, xiaxue, NULL, NULL);
	Node* xiayu = new Node("����", 1, 85, 1915, -1, 4, pinru, xiayu, NULL, NULL);
	Node* gaoshou = new Node("����", 1, 82, 1884, 1966, 3, wenyan, NULL, NULL, NULL);
	Node* gaoren = new Node("����", 1, 92, 1888, 1980, 3, wenyan, gaoshou, NULL, NULL);
	Node* daer = new Node("����", 1, 72, 1888, 1960, 3, shixian, NULL, NULL, NULL);
	Node* xiaoren = new Node("��С��", 0, 87, 1890, 1977, 3, shixian, daer, NULL, NULL);
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
			cout << "�����������������" << endl;
			cin.clear();
			cin.sync();
			Sleep(500);
			system("cls");
			continue;
		}//�ж����x����int���ͣ��������������� 
		system("cls");
		vector<Node*> vec;
		switch (x) {
		case 1:
			t.Insert();
			break;
		case 2:
			cout << "������Ҫ��ta�Ӽ������Ƴ����˵����֣�";
			cin >> a;
			t.Delete(a);
			break;
		case 3:
			cout << "���������ȡ��Ϣ���˵����֣�";
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
			cout << "�Լ��ײ������������ռ�����ʾΪ��" << endl;
			t.Display();
			break;
		default:
			cout << "�����������������" << endl;
			break;
		}
		if (x == 6) break;
		cout << "\n\t\t\t�����������...";
		_getch();
		system("cls");
	}
	return 0;
}

