#include <bits/stdc++.h>
#include <windows.h> 
#define len 18
#define deep 2 
using namespace std;

char a[len+1][len+1];
int vis[len+1][len+1][4];

void print() { // ������� 
	for (int i=1; i<=len; i++) cout << "----";
	cout << "-" << endl;
	for (int i=1; i<=len; i++) {
		for (int j=1; j<=len; j++) cout << "| " << a[i][j] << " ";
		cout << "| " << len-i+1 << endl;
		for (int j=1; j<=len; j++) cout << "----";
		cout << "-" << endl;
	}
	for (int i=1; i<=len; i++) {
		if (i < 10) cout << "  " << i << " ";
		else cout << " " << i << " ";
	}
	cout << endl << endl; 
}

int judge(char c) { // ��ǰ�������֡� c���������� 
	int num = 0, count, jud;
	memset(vis, 0, sizeof(vis));
	for (int i=1; i<=len; i++) {
		for (int j=1; j<=len; j++) {
			if (a[i][j] == c) {
				if (vis[i][j][0] == 0) { // �����ж� 
					count = 1; jud = 0; vis[i][j][0] = 1;
					if (j == 1 or (a[i][j-1] != ' ' and a[i][j-1] != c)) jud++; // ��������� 
					for (int k=1; k<5; k++) {
						if (a[i][j+k] == c) { count++; vis[i][j+k][0] = 1; } // ��������ͬ������ 
						else if (a[i][j+k] == ' ') break; // �����λ 
						else { jud++; break; } // ������������������ 
						if (j+k == len) { jud++; break; } // �ұߵ��˱߽� 
					}
					if (count >= 5) num += 1e6; // ʤ����ȡ1e6��������~ 
					else if (count > 1) {
						if (jud == 0) num += pow(10, count); // ���/��/�� 
						else if (jud == 1) num += pow(10, count-1); // �߶�/��/���� 
					}
				}
				if (vis[i][j][1] == 0) { // �����ж� 
					count = 1; jud = 0; vis[i][j][1] = 1;
					if (i == 1 or (a[i-1][j] != ' ' and a[i-1][j] != c)) jud++; // ���������� 
					for (int k=1; k<5; k++) {
						if (a[i+k][j] == c) { count++; vis[i+k][j][1] = 1; } // ��������ͬ������ 
						else if (a[i+k][j] == ' ') break; // �����λ 
						else { jud++; break; } // ������������������ 
						if (i+k == len) { jud++; break; } // ���浽�˱߽� 
					}
					if (count >= 5) num += 1e6; // ʤ����ȡ1e6��������~ 
					else if (count > 1) {
						if (jud == 0) num += pow(10, count); // ���/��/�� 
						else if (jud == 1) num += pow(10, count-1); // �߶�/��/���� 
					}
				}
				if (vis[i][j][2] == 0) { // ����-����б�� 
					count = 1; jud = 0; vis[i][j][2] = 1;
					if (i == 1 or j == 1 or (a[i-1][j-1] != ' ' and a[i-1][j-1] != c)) jud++; // ���������� 
					for (int k=1; k<5; k++) {
						if (a[i+k][j+k] == c) { count++; vis[i+k][j+k][2] = 1; } // ��������ͬ������ 
						else if (a[i+k][j+k] == ' ') break; // ���¿�λ 
						else { jud++; break; } // ������������������ 
						if (i+k == len or j+k == len) { jud++; break; } // ���µ��˱߽� 
					}
					if (count >= 5) num += 1e6; // ʤ����ȡ1e6��������~ 
					else if (count > 1) {
						if (jud == 0) num += pow(10, count); // ���/��/�� 
						else if (jud == 1) num += pow(10, count-1); // �߶�/��/���� 
					}
				}
				if (vis[i][j][3] == 0) { // ����-����б�� 
					count = 1; jud = 0; vis[i][j][3] = 1;
					if (i == 1 or j == len or (a[i-1][j+1] != ' ' and a[i-1][j+1] != c)) jud++; // ���������� 
					for (int k=1; k<5; k++) {
						if (a[i+k][j-k] == c) { count++; vis[i+k][j-k][3] = 1; } // ��������ͬ������ 
						else if (a[i+k][j-k] == ' ') break; // ���¿�λ 
						else { jud++; break; } // ������������������ 
						if (i+k == len or j-k == 1) { jud++; break; } // ���µ��˱߽� 
					}
					if (count >= 5) num += 1e6; // ʤ����ȡ1e6��������~ 
					else if (count > 1) {
						if (jud == 0) num += pow(10, count); // ���/��/�� 
						else if (jud == 1) num += pow(10, count-1); // �߶�/��/���� 
					}
				}
			}
		}
	}
	return num;
} 

int x[deep], y[deep], ma[deep+1], mi[deep+1];

int minimax(char c,int l) {
	int t = judge('x')-judge('o'); // �жϵ�ǰ���� 
	if (t > 1e5 or t < -1e5 or l == deep) return t; // �Ѿ�ʤ��/�ﵽ��ȣ�ֱ�ӷ���
	int ans = (c == 'x' ? -1e9 : 1e9);  
	ma[l+1] = -1e9; mi[l+1] = 1e9; // ��ʼ�����������ֵܽڵ��е����/���ֵ 
	int vis[len+1][len+1];
	memset(vis, 0, sizeof(vis));
	for (int i=5; i<=len-4; i++) { // �����������в� 
		for (int j=5; j<=len-4; j++) {
			if (a[i][j] == ' ' and vis[i][j] == 0) {
				vis[i][j] = 1;
				a[i][j] = c;
				if (c == 'x') { // max
					int sum = minimax('o', l+1);
					if (sum > ans) { // �ӽڵ������ֵ 
						ans = sum; x[l] = i; y[l] = j;
					} 
					if (sum >= mi[l]) { // a >= b����֦ 
						a[i][j] = ' ';
						return sum;
					}
				}
				else { // min
					int sum = minimax('x', l+1);
					if (sum < ans) { // �ӽڵ������ֵ 
						ans = sum; x[l] = i; y[l] = j;
					}
					if (sum <= ma[l]) { // b <= a����֦ 
						a[i][j] = ' ';
						return sum;
					}
				}
				a[i][j] = ' '; // ���� 
			}
		}
	}
	for (int i=1; i<=len; i++) { // �������ⲿ�����������ȫ��ͬ~ 
		for (int j=1; j<=len; j++) {
			if (a[i][j] == ' ' and vis[i][j] == 0) {
				vis[i][j] = 1;
				a[i][j] = c;
				if (c == 'x') { // max
					int sum = minimax('o', l+1);
					if (sum > ans) { // �ӽڵ������ֵ 
						ans = sum; x[l] = i; y[l] = j;
					} 
					if (sum >= mi[l]) { // a >= b����֦ 
						a[i][j] = ' ';
						return sum;
					}
				}
				else { // min
					int sum = minimax('x', l+1);
					if (sum < ans) { // �ӽڵ������ֵ 
						ans = sum; x[l] = i; y[l] = j;
					}
					if (sum <= ma[l]) { // b <= a����֦ 
						a[i][j] = ' ';
						return sum;
					}
				}
				a[i][j] = ' '; // ���� 
			}
		}
	}
	mi[l] = min(mi[l], ans); // ���±��������ֵܽڵ����/���ֵ 
	ma[l] = max(ma[l], ans);
	return ans;
}

int main() {
	int i,j; char m; system("mode con cols=120 lines=46");
	// ����ģʽ  
	cout << "Would you like to take first? (Enter 1 to take first, enter 2 to take second, enter else to watch two AI battle~)" << endl;
	cin >> m;
	// ��ʼ������ 
	system("cls");
	for (i=1; i<=len; i++) 
		for (j=1; j<=len; j++)
			a[i][j] = ' ';
	a[len/2][len/2] = 'x';
	a[len/2][len/2+1] = 'x';
	a[len/2+1][len/2] = 'o';
	a[len/2][len/2-1] = 'o';
	int cou = 10,c = 'x', yourx, youry, t = len*len-6;
	// ��ʼ�Ծ� 
	while (--t) {
		if (m == '1') { // ����
			print(); // ������� 
			int ans = judge('x')-judge('o'); // ���㵱ǰ���� 
			if (-ans >= 1e5) { // ����~ 
				cout << "You lose >_<" << endl;
				break;
			}
			cout << "x score: " << ans << "     o score: " << -ans << endl; // ������� 
			if (x[0] != 0 or y[0] != 0) cout << endl << "AI's choice:  " << y[0] << " " << len-x[0]+1 << endl; // ���AI��һ���ľ��� 
			cout << endl << "Your choice:  "; 
			cin >> yourx >> youry;
			while (a[len-youry+1][yourx] != ' ' or len-youry+1 > len or len-youry+1 < 1 or youry > len or youry < 1) { // �ж������Ƿ���� 
				cout << "You can't take this place! Choose another one:  ";
				cin >> yourx >> youry;
			}
			a[len-youry+1][yourx] = c; // ע���Ƕ�ά���꣬���Ǿ������� 
			system("cls"); // ���� 
			print(); // ������� 
			c = (c == 'x' ? 'o' : 'x'); // ��һ�������� 
			ans = judge('x')-judge('o'); // ���㵱ǰ���� 
			if (ans >= 1e5) { // Ӯ��~ 
				cout << "You win ^_^" << endl;
				break;
			}
			cout << "x score: " << ans << "     o score: " << -ans << endl; // ������� 
			cout << endl << "AI is thinking..." << endl;
			ma[0] = -1e9; mi[0] = 1e9; // ��ʼ���ֵܽڵ� 
			ans = minimax(c, 0); // min_max���� 
			system("cls"); // ���� 
			a[x[0]][y[0]] = c; // AI���� 
			c = (c == 'x' ? 'o' : 'x'); // ��һ�������� 
		}
		else if (m == '2') { // ����
			ma[0] = -1e9; mi[0] = 1e9; // ��ʼ���ֵܽڵ�  
			int ans = minimax(c, 0); // min_max���� 
			system("cls"); // ���� 
			a[x[0]][y[0]] = c; // AI���� 
			c = (c == 'x' ? 'o' : 'x'); // ��һ�������� 
			print(); // ������� 
			ans = judge('x')-judge('o'); // ���㵱ǰ���� 
			if (ans >= 1e5) { // ����~ 
				cout << "You lose >_<" << endl;
				break;
			}
			cout << "x score: " << ans << "     o score: " << -ans << endl; // ������� 
			if (x[0] != 0 or y[0] != 0) cout << endl << "AI's choice:  " << y[0] << " " << len-x[0]+1 << endl;  // ���AI��һ���ľ��� 
			cout << endl << "Your choice:  "; 
			cin >> yourx >> youry;
			while (a[len-youry+1][yourx] != ' ' or len-youry+1 > len or len-youry+1 < 1 or youry > len or youry < 1) { // �ж������Ƿ���� 
				cout << "You can't take this place! Choose another one:  ";
				cin >> yourx >> youry;
			}
			a[len-youry+1][yourx] = c; // ע���Ƕ�ά���꣬���Ǿ������� 
			system("cls"); // ���� 
			print(); // ������� 
			c = (c == 'x' ? 'o' : 'x'); // ��һ�������� 
			ans = judge('x')-judge('o'); // ���㵱ǰ���� 
			if (-ans >= 1e5) { // Ӯ��~ 
				cout << "You win ^_^" << endl;
				break;
			}
			cout << "x score: " << ans << "     o score: " << -ans << endl; // ������� 
			cout << endl << "AI is thinking..." << endl;
		}
		else {
			ma[0] = -1e9; mi[0] = 1e9; // ��ʼ���ֵܽڵ�  
			int ans = minimax(c, 0); // min_max���� 
			system("cls"); // ���� 
			a[x[0]][y[0]] = c; // AI���� 
			c = (c == 'x' ? 'o' : 'x'); // ��һ�������� 
			print(); // ������� 
			ans = judge('x')-judge('o'); // ���㵱ǰ���� 
			if (ans >= 1e5 or ans <= -1e5) { // ����~ 
				cout << "Battle end~" << endl;
				break;
			}
			cout << "x score: " << ans << "     o score: " << -ans << endl; // ������� 
			if (x[0] != 0 or y[0] != 0) cout << endl << "AI's choice:  " << y[0] << " " << len-x[0]+1 << endl;  // ���AI��һ���ľ��� 
			Sleep(1000); // Ъһ�ᣬ�����û�������AI����~ 
		}
	}
	if (t == 0) cout << "Battle end~" << endl;
} 
