/*
#############################################################
##  姓名：宋渝杰、黄思蓉
##  文件说明：cuda大作业“TSP问题”cpu贪心算法程序
#############################################################
*/

#include <iostream>
#include <algorithm>
#include <sys/time.h>
#include <cmath>
using namespace std;

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
##  函数：main
##  函数描述：主函数，负责文件输入、调用函数、输出最优结果。
##  参数描述：
##  int argc, char* argv[]：可变输入参数，实际上只接受第一个输入，即输入文件名
#############################################################
*/

int main(int argc, char* argv[]) {
    
    // 读入城市位置
    if (readInFlie) freopen(argv[1], "r", stdin);
    int n;
    scanf("%d", &n);
    int x[n], y[n], vis[n], R[n], r[n], now, index;
    for (int i = 0; i < n; i++) scanf("%d%d", &x[i], &y[i]);
    
    // 贪心算法
    timeval t1, t2;
    gettimeofday(&t1, NULL);
    double ans = 1e18, sum = 0, mi;
    for (int i = 0; i < n; i++) {                                 // 初始化起点为城市i
        for (int j = 0; j < n; j++) vis[j] = 0;
        sum = 0, now = i, r[0] = i, vis[i] = 1;
        for (int j = 1; j < n; j++) {
            mi = 1e18;
            for (int k = 0; k < n; k++) {
                if (vis[k] == 0 and cal(x[now], y[now], x[k], y[k]) < mi) {
                    mi = cal(x[now], y[now], x[k], y[k]);         // 选择离目前城市最近的城市作为下一个城市
                    index = k;
                }
            }
            r[j] = index;
            vis[index] = 1;
            now = index;
            sum += mi;
        }
        sum += cal(x[now], y[now], x[i], y[i]);                   // 回到起点
        if (sum < ans) {
            ans = sum;                                            // 记录最优长度和路径
            for (int j = 0; j < n; j++) R[j] = r[j];
        }
    }
    gettimeofday(&t2, NULL);
    
    // 输出贪心结果
    printf("Time: %.4fs\n", (t2.tv_sec-t1.tv_sec+(t2.tv_usec-t1.tv_usec)/1.0e6));
    printf("Path: ");
    for (int i = 0; i < n; i++) printf("%d -> ", R[i]);
    printf("%d\nLength: %8.2f\n", R[0], ans);
}