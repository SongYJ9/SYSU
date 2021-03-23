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
	a[7] = 'R';//初始数组 
	bool t = true;
	system("cls");
	while(t) {
		cout << "\n             ---数组主界面---\n\n";
		cout << "        1.Create              2.Statistics\n";
		cout << "        3.Insert              4.Delete\n";
		cout << "        5.Display             6.Quit\n";
		cout << "        请选择操作：";
		cin >> choice;
		switch (choice) 
		{
			case 1:
				cout << endl << "     请输入数组的大小：" << endl;
				cin >> l2;
				a = new char[l2];//新建新数组 
				l = 0;
				cout << endl << "     Create successful!" << endl;
				break;
			case 2:
				cout << endl << "     数组的长度： " << l;
				cout << endl << "     数组的容量： " << l2 << endl;
				break;
			case 3:
				cout << endl << "     请输入字符和插入的位置：" << endl;
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
						cout << endl << "     插入位置超出数组长度！" << endl;
					}
				}
				else {
					cout << endl << "     数组容量已满！" << endl;
				}
				break;
			case 4:
				cout << endl << "     请输入删除的位置：" << endl;
				cin >> n;
				if (n < l) {
					for (int i = n; i < l; i++) {
						a[i] = a[i + 1];
					}
					l--;
				}
				else {
					cout << endl << "     删除位置超出数组长度！" << endl;
				}
				break;
			case 5://输出数据内容 
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
