#include <bits/stdc++.h>
#include <windows.h> 
#define len 18
#define deep 2 
using namespace std;

char a[len+1][len+1];
int vis[len+1][len+1][4];

void print() { // 输出棋盘 
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

int judge(char c) { // 当前局势评分。 c：棋子类型 
	int num = 0, count, jud;
	memset(vis, 0, sizeof(vis));
	for (int i=1; i<=len; i++) {
		for (int j=1; j<=len; j++) {
			if (a[i][j] == c) {
				if (vis[i][j][0] == 0) { // 横向判断 
					count = 1; jud = 0; vis[i][j][0] = 1;
					if (j == 1 or (a[i][j-1] != ' ' and a[i][j-1] != c)) jud++; // 左边有阻拦 
					for (int k=1; k<5; k++) {
						if (a[i][j+k] == c) { count++; vis[i][j+k][0] = 1; } // 横向连续同类棋子 
						else if (a[i][j+k] == ' ') break; // 横向空位 
						else { jud++; break; } // 横向有其他棋子阻拦 
						if (j+k == len) { jud++; break; } // 右边到了边界 
					}
					if (count >= 5) num += 1e6; // 胜利，取1e6近似无穷~ 
					else if (count > 1) {
						if (jud == 0) num += pow(10, count); // 活二/三/四 
						else if (jud == 1) num += pow(10, count-1); // 眠二/三/冲四 
					}
				}
				if (vis[i][j][1] == 0) { // 纵向判断 
					count = 1; jud = 0; vis[i][j][1] = 1;
					if (i == 1 or (a[i-1][j] != ' ' and a[i-1][j] != c)) jud++; // 上面有阻拦 
					for (int k=1; k<5; k++) {
						if (a[i+k][j] == c) { count++; vis[i+k][j][1] = 1; } // 纵向连续同类棋子 
						else if (a[i+k][j] == ' ') break; // 纵向空位 
						else { jud++; break; } // 纵向有其他棋子阻拦 
						if (i+k == len) { jud++; break; } // 下面到了边界 
					}
					if (count >= 5) num += 1e6; // 胜利，取1e6近似无穷~ 
					else if (count > 1) {
						if (jud == 0) num += pow(10, count); // 活二/三/四 
						else if (jud == 1) num += pow(10, count-1); // 眠二/三/冲四 
					}
				}
				if (vis[i][j][2] == 0) { // 左上-右下斜线 
					count = 1; jud = 0; vis[i][j][2] = 1;
					if (i == 1 or j == 1 or (a[i-1][j-1] != ' ' and a[i-1][j-1] != c)) jud++; // 左上有阻拦 
					for (int k=1; k<5; k++) {
						if (a[i+k][j+k] == c) { count++; vis[i+k][j+k][2] = 1; } // 右下连续同类棋子 
						else if (a[i+k][j+k] == ' ') break; // 右下空位 
						else { jud++; break; } // 右下有其他棋子阻拦 
						if (i+k == len or j+k == len) { jud++; break; } // 右下到了边界 
					}
					if (count >= 5) num += 1e6; // 胜利，取1e6近似无穷~ 
					else if (count > 1) {
						if (jud == 0) num += pow(10, count); // 活二/三/四 
						else if (jud == 1) num += pow(10, count-1); // 眠二/三/冲四 
					}
				}
				if (vis[i][j][3] == 0) { // 右上-左下斜线 
					count = 1; jud = 0; vis[i][j][3] = 1;
					if (i == 1 or j == len or (a[i-1][j+1] != ' ' and a[i-1][j+1] != c)) jud++; // 右上有阻拦 
					for (int k=1; k<5; k++) {
						if (a[i+k][j-k] == c) { count++; vis[i+k][j-k][3] = 1; } // 左下连续同类棋子 
						else if (a[i+k][j-k] == ' ') break; // 左下空位 
						else { jud++; break; } // 左下有其他棋子阻拦 
						if (i+k == len or j-k == 1) { jud++; break; } // 左下到了边界 
					}
					if (count >= 5) num += 1e6; // 胜利，取1e6近似无穷~ 
					else if (count > 1) {
						if (jud == 0) num += pow(10, count); // 活二/三/四 
						else if (jud == 1) num += pow(10, count-1); // 眠二/三/冲四 
					}
				}
			}
		}
	}
	return num;
} 

int x[deep], y[deep], ma[deep+1], mi[deep+1];

int minimax(char c,int l) {
	int t = judge('x')-judge('o'); // 判断当前局势 
	if (t > 1e5 or t < -1e5 or l == deep) return t; // 已经胜利/达到深度，直接返回
	int ans = (c == 'x' ? -1e9 : 1e9);  
	ma[l+1] = -1e9; mi[l+1] = 1e9; // 初始化遍历过的兄弟节点中的最高/最低值 
	int vis[len+1][len+1];
	memset(vis, 0, sizeof(vis));
	for (int i=5; i<=len-4; i++) { // 先搜索棋盘中部 
		for (int j=5; j<=len-4; j++) {
			if (a[i][j] == ' ' and vis[i][j] == 0) {
				vis[i][j] = 1;
				a[i][j] = c;
				if (c == 'x') { // max
					int sum = minimax('o', l+1);
					if (sum > ans) { // 子节点中最高值 
						ans = sum; x[l] = i; y[l] = j;
					} 
					if (sum >= mi[l]) { // a >= b，剪枝 
						a[i][j] = ' ';
						return sum;
					}
				}
				else { // min
					int sum = minimax('x', l+1);
					if (sum < ans) { // 子节点中最低值 
						ans = sum; x[l] = i; y[l] = j;
					}
					if (sum <= ma[l]) { // b <= a，剪枝 
						a[i][j] = ' ';
						return sum;
					}
				}
				a[i][j] = ' '; // 回溯 
			}
		}
	}
	for (int i=1; i<=len; i++) { // 再搜索外部，下面代码完全相同~ 
		for (int j=1; j<=len; j++) {
			if (a[i][j] == ' ' and vis[i][j] == 0) {
				vis[i][j] = 1;
				a[i][j] = c;
				if (c == 'x') { // max
					int sum = minimax('o', l+1);
					if (sum > ans) { // 子节点中最高值 
						ans = sum; x[l] = i; y[l] = j;
					} 
					if (sum >= mi[l]) { // a >= b，剪枝 
						a[i][j] = ' ';
						return sum;
					}
				}
				else { // min
					int sum = minimax('x', l+1);
					if (sum < ans) { // 子节点中最低值 
						ans = sum; x[l] = i; y[l] = j;
					}
					if (sum <= ma[l]) { // b <= a，剪枝 
						a[i][j] = ' ';
						return sum;
					}
				}
				a[i][j] = ' '; // 回溯 
			}
		}
	}
	mi[l] = min(mi[l], ans); // 更新遍历过的兄弟节点最高/最低值 
	ma[l] = max(ma[l], ans);
	return ans;
}

int main() {
	int i,j; char m; system("mode con cols=120 lines=46");
	// 输入模式  
	cout << "Would you like to take first? (Enter 1 to take first, enter 2 to take second, enter else to watch two AI battle~)" << endl;
	cin >> m;
	// 初始化棋盘 
	system("cls");
	for (i=1; i<=len; i++) 
		for (j=1; j<=len; j++)
			a[i][j] = ' ';
	a[len/2][len/2] = 'x';
	a[len/2][len/2+1] = 'x';
	a[len/2+1][len/2] = 'o';
	a[len/2][len/2-1] = 'o';
	int cou = 10,c = 'x', yourx, youry, t = len*len-6;
	// 开始对局 
	while (--t) {
		if (m == '1') { // 先手
			print(); // 输出棋盘 
			int ans = judge('x')-judge('o'); // 计算当前局势 
			if (-ans >= 1e5) { // 输了~ 
				cout << "You lose >_<" << endl;
				break;
			}
			cout << "x score: " << ans << "     o score: " << -ans << endl; // 输出分数 
			if (x[0] != 0 or y[0] != 0) cout << endl << "AI's choice:  " << y[0] << " " << len-x[0]+1 << endl; // 输出AI上一步的决策 
			cout << endl << "Your choice:  "; 
			cin >> yourx >> youry;
			while (a[len-youry+1][yourx] != ' ' or len-youry+1 > len or len-youry+1 < 1 or youry > len or youry < 1) { // 判断输入是否合理 
				cout << "You can't take this place! Choose another one:  ";
				cin >> yourx >> youry;
			}
			a[len-youry+1][yourx] = c; // 注意是二维坐标，不是矩阵坐标 
			system("cls"); // 清屏 
			print(); // 输出棋盘 
			c = (c == 'x' ? 'o' : 'x'); // 下一步的棋子 
			ans = judge('x')-judge('o'); // 计算当前局势 
			if (ans >= 1e5) { // 赢了~ 
				cout << "You win ^_^" << endl;
				break;
			}
			cout << "x score: " << ans << "     o score: " << -ans << endl; // 输出分数 
			cout << endl << "AI is thinking..." << endl;
			ma[0] = -1e9; mi[0] = 1e9; // 初始化兄弟节点 
			ans = minimax(c, 0); // min_max搜索 
			system("cls"); // 清屏 
			a[x[0]][y[0]] = c; // AI下棋 
			c = (c == 'x' ? 'o' : 'x'); // 下一步的棋子 
		}
		else if (m == '2') { // 后手
			ma[0] = -1e9; mi[0] = 1e9; // 初始化兄弟节点  
			int ans = minimax(c, 0); // min_max搜索 
			system("cls"); // 清屏 
			a[x[0]][y[0]] = c; // AI下棋 
			c = (c == 'x' ? 'o' : 'x'); // 下一步的棋子 
			print(); // 输出棋盘 
			ans = judge('x')-judge('o'); // 计算当前局势 
			if (ans >= 1e5) { // 输了~ 
				cout << "You lose >_<" << endl;
				break;
			}
			cout << "x score: " << ans << "     o score: " << -ans << endl; // 输出分数 
			if (x[0] != 0 or y[0] != 0) cout << endl << "AI's choice:  " << y[0] << " " << len-x[0]+1 << endl;  // 输出AI上一步的决策 
			cout << endl << "Your choice:  "; 
			cin >> yourx >> youry;
			while (a[len-youry+1][yourx] != ' ' or len-youry+1 > len or len-youry+1 < 1 or youry > len or youry < 1) { // 判断输入是否合理 
				cout << "You can't take this place! Choose another one:  ";
				cin >> yourx >> youry;
			}
			a[len-youry+1][yourx] = c; // 注意是二维坐标，不是矩阵坐标 
			system("cls"); // 清屏 
			print(); // 输出棋盘 
			c = (c == 'x' ? 'o' : 'x'); // 下一步的棋子 
			ans = judge('x')-judge('o'); // 计算当前局势 
			if (-ans >= 1e5) { // 赢了~ 
				cout << "You win ^_^" << endl;
				break;
			}
			cout << "x score: " << ans << "     o score: " << -ans << endl; // 输出分数 
			cout << endl << "AI is thinking..." << endl;
		}
		else {
			ma[0] = -1e9; mi[0] = 1e9; // 初始化兄弟节点  
			int ans = minimax(c, 0); // min_max搜索 
			system("cls"); // 清屏 
			a[x[0]][y[0]] = c; // AI下棋 
			c = (c == 'x' ? 'o' : 'x'); // 下一步的棋子 
			print(); // 输出棋盘 
			ans = judge('x')-judge('o'); // 计算当前局势 
			if (ans >= 1e5 or ans <= -1e5) { // 结束~ 
				cout << "Battle end~" << endl;
				break;
			}
			cout << "x score: " << ans << "     o score: " << -ans << endl; // 输出分数 
			if (x[0] != 0 or y[0] != 0) cout << endl << "AI's choice:  " << y[0] << " " << len-x[0]+1 << endl;  // 输出AI上一步的决策 
			Sleep(1000); // 歇一会，方便用户看得清AI操作~ 
		}
	}
	if (t == 0) cout << "Battle end~" << endl;
} 
