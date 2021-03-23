#include <bits/stdc++.h>
#include <Windows.h>
using namespace std;

struct node{
	int x, y, g, h; // 横纵坐标、f = g+h 
}; 

int cmp(node a, node b) {
	return a.g+a.h < b.g+b.h; // f 升序排列 
}

int n, m, stop, limit, num;
int sx, sy, ex, ey; // start end 坐标 
string maze[20]; // 迷宫地图 

void DFS(int x, int y, int g) { // 普通 DFS 时 limit = 10000000（无穷大） 
	num++; // 记录搜索的次数 
	if (maze[x][y] == 'E') {
		stop = 1; // 结束标识符 
		cout << "len: " << g << endl; // 输出路径长度 
		cout << "Road: " << endl; // 输出路径 
		for (int i=0; i<n; i++) cout << maze[i] << endl;
		return;
	}
	if (maze[x][y] == '0') maze[x][y] = 'R';
	if (stop == 0 and (maze[x][y-1] == '0' or maze[x][y-1] == 'E') and g+1 <= limit) DFS(x, y-1, g+1); // 四个方向 DFS 
	if (stop == 0 and (maze[x+1][y] == '0' or maze[x+1][y] == 'E') and g+1 <= limit) DFS(x+1, y, g+1);
	if (stop == 0 and (maze[x][y+1] == '0' or maze[x][y+1] == 'E') and g+1 <= limit) DFS(x, y+1, g+1);
	if (stop == 0 and (maze[x-1][y] == '0' or maze[x-1][y] == 'E') and g+1 <= limit) DFS(x-1, y, g+1);
	maze[x][y] = '0'; // 回溯
}

void IDS(int x, int y) { // IDS 
	while (stop == 0) {
		DFS(x, y, 0);
		limit++; // 限制++ 
		maze[sx][sy] = 'S'; 
	}
}

int h(int x, int y) { // 曼哈顿距离 
	return abs(x-ex)+abs(y-ey);
}

void IDA_DFS(int x, int y, int g) {
	num++; // 记录搜索的次数
	if (maze[x][y] == 'E') {
		stop = 1; // 结束标识符 
		cout << "len: " << g << endl; // 输出路径长度 
		cout << "Road: " << endl; // 输出路径 
		for (int i=0; i<n; i++) cout << maze[i] << endl;
		return;
	}
	if (maze[x][y] == '0') maze[x][y] = 'R';
	node Node[4];
	Node[0].x = x-1; Node[0].y = y; Node[0].g = g+1; Node[0].h = h(x-1, y); // 四个节点 
	Node[1].x = x+1; Node[1].y = y; Node[1].g = g+1; Node[1].h = h(x+1, y);
	Node[2].x = x; Node[2].y = y-1; Node[2].g = g+1; Node[2].h = h(x, y-1);
	Node[3].x = x; Node[3].y = y+1; Node[3].g = g+1; Node[3].h = h(x, y+1);
	sort(Node, Node+4, cmp); // 按照估价函数 f 升序排序 
	for (int i=0; i<4; i++) {
		if (stop == 0 and (maze[Node[i].x][Node[i].y] == '0' or maze[Node[i].x][Node[i].y] == 'E') and Node[i].g+Node[i].h <= limit) 
			IDA_DFS(Node[i].x, Node[i].y, Node[i].g);
	}
	maze[x][y] = '0'; // 回溯 
}

void IDA_star(int x, int y) { // IDA_star 
	while (stop == 0) {
		IDA_DFS(x, y, 0);
		limit++; // 限制++ 
		maze[sx][sy] = 'S'; 
	}
} 

int main() {
	int i, j;
	double time, time2;
	LARGE_INTEGER t1, t2, tc;
    QueryPerformanceFrequency(&tc);
	freopen("MazeData.txt", "r", stdin);
	while (cin >> maze[n]) {
		m = maze[n].length();
		for (j=0; j<m; j++) {
			if (maze[n][j] == 'S') {
				sx = n;
				sy = j;
			}
			if (maze[n][j] == 'E') {
				ex = n;
				ey = j;
			}
		}
		n++;
	}
	
	// DFS
	stop = num = 0;
	limit = 1e7; // 普通 DFS 时 limit 设为无穷大 
	cout << "Normal DFS:" << endl;
	QueryPerformanceCounter(&t1); // 计时 
	DFS(sx, sy, 0);
	QueryPerformanceCounter(&t2);
	time = (double)(t2.QuadPart-t1.QuadPart)/(double)tc.QuadPart; 
	printf("Time: %.4fms\n", time*1000);
	cout << "Search count: " << num << endl << endl;
	// IDS 
	stop = num = 0;
	limit = abs(sx-ex)+abs(sy-ey); // 默认为起点和终点的曼哈顿距离 
	cout << "IDS:" << endl;
	QueryPerformanceCounter(&t1);
	IDS(sx, sy);
	QueryPerformanceCounter(&t2);
	time = (double)(t2.QuadPart-t1.QuadPart)/(double)tc.QuadPart; 
	printf("Time: %.4fms\n", time*1000);
	cout << "Search count: " << num << endl << endl;
	// IDA_star 
	stop = num = 0;
	limit = abs(sx-ex)+abs(sy-ey); // 默认为起点和终点的曼哈顿距离 
	cout << "IDA_star:" << endl;
	QueryPerformanceCounter(&t1);
	IDA_star(sx, sy);
	QueryPerformanceCounter(&t2);
	time = (double)(t2.QuadPart-t1.QuadPart)/(double)tc.QuadPart; 
	printf("Time: %.4fms\n", time*1000);
	cout << "Search count: " << num << endl << endl;
} 
