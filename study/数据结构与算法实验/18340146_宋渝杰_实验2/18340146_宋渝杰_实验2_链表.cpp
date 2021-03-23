#include <iostream>
#include <string>

using namespace std;

struct node 
{
	char c;
	node* next;
};

class List//������ 
{
private:
	node* head;
	int l;
public:
	List() {//���캯�� 
		head = NULL;
		l = 0;
	}
	void Insert(char c, int n) {//���뺯�� ��cΪ�����ַ���nΪ����λ�� 
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
			cout << "      ��ӳɹ���" << endl;
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
			cout << "      ��ӳɹ���" << endl;
		}
		else if (n > l) {
			cout << "������ӷ�Χ��" << endl;
		}
	}
	void Delete(int n) {//ɾ��������nΪɾ��λ�� 
		node* p, * q, * r;
		p = head;
		q = head->next;
		if (n == 0) {
			delete p;
			head = q;
			l--;
			cout << "      ɾ���ɹ���" << endl;
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
			cout << "      ɾ���ɹ���" << endl;
		}
		else if (n >= l) {
			cout << "����ɾ����Χ��" << endl;
		}
	}
	void Display() {//չʾ���� 
		cout << endl << "         ";
		node* p = head;
		for (int i = 0; i < l; i++) {
			cout << p->c << " ";
			p = p->next;
		}
		cout << endl;
	}
	void Statistics() {//ͳ�Ƴ��� 
		cout << endl << "         "<< "length = " << l << endl;
	}
	void Clear() {//������нڵ� 
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
	a->Insert('R', 7);//��ʼ����һ������ 
	system("cls");//����������ʱ��ʾ�ġ���ӳɹ����� 
	while(t) {
		cout << "\n             ---����������---\n\n";
		cout << "        1.Create              2.Statistics\n";
		cout << "        3.Insert              4.Delete\n";
		cout << "        5.Display             6.Quit\n";
		cout << "        ��ѡ�������";
		cin >> choice;
		switch (choice) 
		{
			case 1:
				if(a != NULL) a->Clear();//������������� 
				a = new List();//�½�һ�������� 
				cout << endl << "     Create successful!" << endl;
				break;
			case 2:
				a->Statistics();
				break;
			case 3:
				cout << endl << "     �������ַ��Ͳ����λ�ã�" << endl;
				cin >> c >> n;
				a->Insert(c, n);
				break;
			case 4:
				cout << endl << "     ������ɾ����λ�ã�" << endl;
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
