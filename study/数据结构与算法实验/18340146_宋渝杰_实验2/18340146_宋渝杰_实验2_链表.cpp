#include <iostream>
#include <string>

using namespace std;

struct node 
{
	char c;
	node* next;
};

class List//链表类 
{
private:
	node* head;
	int l;
public:
	List() {//构造函数 
		head = NULL;
		l = 0;
	}
	void Insert(char c, int n) {//插入函数 ，c为插入字符，n为插入位置 
		node* p, * q, * r;
		p = head;
		if (l > 0)	q = head->next;
		else q = head;
		if (n == 0) {
			r = new node();
			r->c = c;
			r->next = p;
			head = r;
			l++;
			cout << "      添加成功！" << endl;
		}
		else if (n <= l) {
			for (int i = 1; i < n; i++) {
				p = q;
				q = q->next;
			}
			r = new node();
			r->c = c;
			r->next = q;
			p->next = r;
			l++;
			cout << "      添加成功！" << endl;
		}
		else if (n > l) {
			cout << "超出添加范围！" << endl;
		}
	}
	void Delete(int n) {//删除函数，n为删除位置 
		node* p, * q, * r;
		p = head;
		q = head->next;
		if (n == 0) {
			delete p;
			head = q;
			l--;
			cout << "      删除成功！" << endl;
		}
		else if (n < l) {
			for (int i = 1; i < n; i++) {
				p = q;
				q = q->next;
			}
			r = q->next;
			delete q;
			p->next = r;
			l--;
			cout << "      删除成功！" << endl;
		}
		else if (n >= l) {
			cout << "超出删除范围！" << endl;
		}
	}
	void Display() {//展示函数 
		cout << endl << "         ";
		node* p = head;
		for (int i = 0; i < l; i++) {
			cout << p->c << " ";
			p = p->next;
		}
		cout << endl;
	}
	void Statistics() {//统计长度 
		cout << endl << "         "<< "length = " << l << endl;
	}
	void Clear() {//清除所有节点 
		node* p = head;
		if (p != NULL) {
			node* q = head->next;
			while (q != NULL) {
				delete p;
				p = q;
				q = q->next;
			}
		}
		delete p;
		head = NULL;
		l = 0;
	}
};

int main()
{
	int choice,n;
	char c;
	bool t = true;
	List* a = new List();
	a->Insert('C', 0);
	a->Insert('O', 1);
	a->Insert('M', 2);
	a->Insert('P', 3);
	a->Insert('U', 4);
	a->Insert('T', 5);
	a->Insert('E', 6);
	a->Insert('R', 7);//初始创造一个链表 
	system("cls");//清除上面插入时显示的“添加成功！” 
	while(t) {
		cout << "\n             ---链表主界面---\n\n";
		cout << "        1.Create              2.Statistics\n";
		cout << "        3.Insert              4.Delete\n";
		cout << "        5.Display             6.Quit\n";
		cout << "        请选择操作：";
		cin >> choice;
		switch (choice) 
		{
			case 1:
				if(a != NULL) a->Clear();//清除旧链表内容 
				a = new List();//新建一个空链表 
				cout << endl << "     Create successful!" << endl;
				break;
			case 2:
				a->Statistics();
				break;
			case 3:
				cout << endl << "     请输入字符和插入的位置：" << endl;
				cin >> c >> n;
				a->Insert(c, n);
				break;
			case 4:
				cout << endl << "     请输入删除的位置：" << endl;
				cin >> n;
				a->Delete(n);
				break;
			case 5:
				a->Display();
				break;
			case 6:
				t = false;
				break;
			default:
				cout << endl << "     Wrong choice!" << endl;
		}
	}
}
