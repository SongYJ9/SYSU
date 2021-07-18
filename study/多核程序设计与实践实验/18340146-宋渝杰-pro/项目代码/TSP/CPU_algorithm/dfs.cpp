/*
#############################################################
##  姓名：宋渝杰、黄思蓉
##  文件说明：cuda大作业“TSP问题”cpu深搜算法程序
#############################################################
*/

#include <iostream>
#include <algorithm>
#include <sys/time.h>
#include <cmath>
using namespace std;

int n;
double ans = 1e9;
int x[100], y[100], vis[100], R[100], r[100];
bool readInFlie = true;

/*
#############################################################
##  函数：cal
##  函数描述：计算两点之间的距离
##  参数描述：
##  int X_x：城市X的x坐标
##  int X_y：城市X的y坐标
##  int Y_x：城市Y的x坐标
##  int Y_y：城市Y的y坐标
#############################################################
*/

double cal(int X_x, int X_y, int Y_x, int Y_y) {
    return sqrt(pow(X_x - Y_x, 2) + pow(X_y - Y_y, 2));
}

/*
#############################################################
##  函数：dfs
##  函数描述：通过深搜枚举所有哈密顿回路，过程中找出最优路径
##  参数描述：
##  int root：当前城市
##  int fa：上一个城市
##  int num：已经过的城市数量
##  double l：已经过的路径长度和
#############################################################
*/

void dfs(int root, int fa, int num, double l) {
    if (l > ans) return;                                         // 深搜剪枝
    vis[root] = 1;
    r[num] = root;
    l += cal(x[fa], y[fa], x[root], y[root]);
    if (num == n-1) {                                            // 已遍历完一次哈密顿回路
        if (l + cal(x[root], y[root], x[0], y[0]) < ans) {
            ans = l + cal(x[root], y[root], x[0], y[0]);         // 记录最优长度和路径
            for (int i = 0; i < n; i++) R[i] = r[i];
        }
    }
    for (int i = 0; i < n; i++)
        if (vis[i] == 0) dfs(i, root, num+1, l);
    vis[root] = 0;
}

/*
#############################################################
##  函数：main
##  函数描述：主函数，负责文件输入、调用函数、输出最优结果。
##  参数描述：
##  int argc, char* argv[]：可变输入参数，实际上只接受第一个输入，即输入文件名
#############################################################
*/

int main(int argc, char* argv[]) {

    // 读入城市位置
    if (readInFlie) freopen(argv[1], "r", stdin);
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d%d", &x[i], &y[i]);
    
    // 深搜算法
    timeval t1, t2;
    gettimeofday(&t1, NULL);
    vis[0] = 1, r[0] = 0;
    for (int i = 1; i < n; i++) dfs(i, 0, 1, 0.0);
    gettimeofday(&t2, NULL);
    
    // 输出精确结果
    printf("Time: %.4fs\n", (t2.tv_sec-t1.tv_sec+(t2.tv_usec-t1.tv_usec)/1.0e6));
    printf("Path: ");
    for (int i = 0; i < n; i++) printf("%d -> ", R[i]);
    printf("%d\nLength: %8.2f\n", R[0], ans);
}