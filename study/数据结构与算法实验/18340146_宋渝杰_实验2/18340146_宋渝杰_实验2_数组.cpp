#include <iostream>
#include <string>

using namespace std;

int main()
{
	int choice,n,l=8,l2 = 10;
	char c;
	char* a = new char[10];
	a[0] = 'C';
	a[1] = 'O';
	a[2] = 'M';
	a[3] = 'P';
	a[4] = 'U';
	a[5] = 'T';
	a[6] = 'E';
	a[7] = 'R';//��ʼ���� 
	bool t = true;
	system("cls");
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
				cout << endl << "     ����������Ĵ�С��" << endl;
				cin >> l2;
				a = new char[l2];//�½������� 
				l = 0;
				cout << endl << "     Create successful!" << endl;
				break;
			case 2:
				cout << endl << "     ����ĳ��ȣ� " << l;
				cout << endl << "     ����������� " << l2 << endl;
				break;
			case 3:
				cout << endl << "     �������ַ��Ͳ����λ�ã�" << endl;
				cin >> c >> n;
				if (l < l2) {
					if (n <= l) {
						for (int i = l - 1; i >= n; i--) {
							a[i + 1] = a[i];
						}
						a[n] = c;
						l++;
					}
					else if (n > l) {
						cout << endl << "     ����λ�ó������鳤�ȣ�" << endl;
					}
				}
				else {
					cout << endl << "     ��������������" << endl;
				}
				break;
			case 4:
				cout << endl << "     ������ɾ����λ�ã�" << endl;
				cin >> n;
				if (n < l) {
					for (int i = n; i < l; i++) {
						a[i] = a[i + 1];
					}
					l--;
				}
				else {
					cout << endl << "     ɾ��λ�ó������鳤�ȣ�" << endl;
				}
				break;
			case 5://����������� 
				cout << endl;
				for (int i = 0; i < l; i++){
					cout << a[i] << " ";
				}
				cout << endl;
				break;
			case 6:
				t = false;
				break;
			default:
				cout << endl << "     Wrong choice!" << endl;
		}
	}
}
