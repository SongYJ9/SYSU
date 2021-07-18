/*
#############################################################
##  姓名：宋渝杰、黄思蓉
##  文件说明：cuda大作业“模拟退火解决TSP问题”CPU单线程模拟退火算法程序
#############################################################
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#define Length 20000
#define Tstart 1e8
#define Tend 1e-12

bool readInFlie = true;

/*
#############################################################
##  函数：dis
##  函数描述：计算两点之间的距离
##  参数描述：
##  int X_x：城市X的x坐标
##  int X_y：城市X的y坐标
##  int Y_x：城市Y的x坐标
##  int Y_y：城市Y的y坐标
#############################################################
*/

double dis(int X_x, int X_y, int Y_x, int Y_y) {
    return sqrt(pow(X_x - Y_x, 2) + pow(X_y - Y_y, 2));
}

/*
#############################################################
##  函数：SA_TSP_Serial
##  函数描述：串行模拟退火算法解决TSP问题
##  参数描述：
##  int *x：城市的x坐标
##  int *y：城市的y坐标
##  int n：城市个数
##  int *path：返回最优线程的回路路径
##  double *len：返回最优线程的回路长度
#############################################################
*/

void SA_TSP_Serial(int *x, int *y, int n, int *ans, double *len) {

    // 初始化工作
    long long count = 0;
    int *threadPath = new int[n], *changePath = new int[n+1];          // 线程计算的回路路线
    double threadLen = 0, delta = 0;                                   // 线程计算的回路长度
    double T = Tstart, alpha = 0.95;                                   // 模拟退火的温度和降温率
    int L = Length, way = 0, t1, t2, mid, r;                           // 每个温度T的迭代次数，以及sa的辅助变量
    for (int i = 0; i < n; i++) changePath[i] = threadPath[i] = i;     // 初始化为0->1->...->n-1->0的回路
    changePath[n] = 0;
    for (int i = 0; i < n; i++) 
        threadLen += dis(x[i], y[i], x[(i+1)%n], y[(i+1)%n]);          // 计算初始回路长度
                         
    // 降温迭代过程
    while (T > Tend) {
        count++;
        if (way == 0) {                                                // 交换相邻的t1、t2两个点
            t1 = rand() % (n - 2) + 1;
            t2 = t1 + 1;
            
            // delta_old = dis(t1-1, t1) + dis(t2, t2+1)
            // delta_new = dis(t1-1, t2) + dis(t1, t2+1)
            delta = dis(x[changePath[t1 - 1]], y[changePath[t1 - 1]], 
                                x[changePath[t2]], y[changePath[t2]])
                        + dis(x[changePath[t1]], y[changePath[t1]], 
                                x[changePath[t2 + 1]], y[changePath[t2 + 1]])
                        - dis(x[changePath[t1 - 1]], y[changePath[t1 - 1]],
                                x[changePath[t1]], y[changePath[t1]])
                        - dis(x[changePath[t2]], y[changePath[t2]], 
                                x[changePath[t2 + 1]], y[changePath[t2 + 1]]);
            int temp = changePath[t1]; 
            changePath[t1] = changePath[t2]; 
            changePath[t2] = temp;
        }
        else if (way == 1) {                                           // 交换任意的t1、t2两个点
            do {
                t1 = rand() % (n - 1) + 1;
                t2 = rand() % (n - 1) + 1;
            } while (t1 + 1 >= t2);
            
            // delta_old = dis(t1-1, t1) + dis(t1, t1+1) + dis(t2-1, t2) + dis(t2, t2+1);
            // delta_new = dis(t1-1, t2) + dis(t2, t1+1) + dis(t2-1, t1) + dis(t1, t2+1);
            delta =  dis(x[changePath[t1 - 1]], y[changePath[t1 - 1]],
                                x[changePath[t2]], y[changePath[t2]])
                        + dis(x[changePath[t2]], y[changePath[t2]], 
                                x[changePath[t1 + 1]], y[changePath[t1 + 1]])
                        + dis(x[changePath[t2 - 1]], y[changePath[t2 - 1]], 
                                x[changePath[t1]], y[changePath[t1]])
                        + dis(x[changePath[t1]], y[changePath[t1]], 
                                x[changePath[t2 + 1]], y[changePath[t2 + 1]])
                        - dis(x[changePath[t1 - 1]], y[changePath[t1 - 1]],
                                x[changePath[t1]], y[changePath[t1]])
                        - dis(x[changePath[t1]], y[changePath[t1]], 
                                x[changePath[t1 + 1]], y[changePath[t1 + 1]])
                        - dis(x[changePath[t2 - 1]], y[changePath[t2 - 1]], 
                                x[changePath[t2]], y[changePath[t2]])
                        - dis(x[changePath[t2]], y[changePath[t2]], 
                                x[changePath[t2 + 1]], y[changePath[t2 + 1]]);
            int temp = changePath[t1];
            changePath[t1] = changePath[t2];
            changePath[t2] = temp;
        }
        else if (way == 2) {                                           // 翻转[t1, t2]序列
            do {
                t1 = rand() % (n - 1) + 1;
                t2 = rand() % (n - 1) + 1;
            } while (t1 + 1 >= t2);
            
            // delta_old = dis(t1-1, t1) + dis(t2, t2+1);
            // delta_new = dis(t1-1, t2) + dis(t1, t2+1);
            delta = dis(x[changePath[t1 - 1]], y[changePath[t1 - 1]], 
                                x[changePath[t2]], y[changePath[t2]])
                        + dis(x[changePath[t1]], y[changePath[t1]], 
                                x[changePath[t2 + 1]], y[changePath[t2 + 1]])
                        - dis(x[changePath[t1 - 1]], y[changePath[t1 - 1]], 
                                x[changePath[t1]], y[changePath[t1]])
                        - dis(x[changePath[t2]], y[changePath[t2]], 
                                x[changePath[t2 + 1]], y[changePath[t2 + 1]]);
            for (int i = t1, j = t2; i < j; i++, j--) {
                int temp = changePath[i];
                changePath[i] = changePath[j];
                changePath[j] = temp;
            }
        }
        else {                                                         // 交换[t1, mid)和[mid, t2)序列
            do {
                mid = rand() % n;
                r = rand() % 10;
            } while (mid - r <= 0 || mid + r >= n);
            t1 = mid - r; t2 = mid + r;
            
            // delta_old = dis(t1-1, t1) + dis(mid-1, mid) + dis(t2-1, t2);
            // delta_new = dis(t1-1, mid) + dis(t2-1, t1) + dis(mid-1, t2);
            delta = dis(x[changePath[t1 - 1]], y[changePath[t1 - 1]], 
                                x[changePath[mid]], y[changePath[mid]])
                        + dis(x[changePath[t2 - 1]], y[changePath[t2 - 1]], 
                                x[changePath[t1]], y[changePath[t1]])
                        + dis(x[changePath[mid - 1]], y[changePath[mid - 1]], 
                                x[changePath[t2]], y[changePath[t2]])
                        - dis(x[changePath[t1 - 1]], y[changePath[t1 - 1]], 
                                x[changePath[t1]], y[changePath[t1]])
                        - dis(x[changePath[mid - 1]], y[changePath[mid - 1]], 
                                x[changePath[mid]], y[changePath[mid]])
                        - dis(x[changePath[t2 - 1]], y[changePath[t2 - 1]], 
                                x[changePath[t2]], y[changePath[t2]]);
            for (int i = t1, j = mid; i < mid; i++, j++) {
                int temp = changePath[i];
                changePath[i] = changePath[j];
                changePath[j] = temp;
            }
        }
        way = (way + 1) % 4;
        
        // 如果变换后回路更优，则接受本次变换，否则以一定概率接受本次变换
        if (delta < 0 || rand() % 100 < exp(-delta / T) * 100) {
            threadLen += delta;
            for (int i = t1; i <= t2; i++) threadPath[i] = changePath[i];
        }
        else {
            for (int i = t1; i <= t2; i++) changePath[i] = threadPath[i];
        }
        
        if (L-- == 0) {
            L = Length;
            T *= alpha;
        }
    }
    
    printf("count: %lld\n", count);    
    for (int i = 0; i < n; i++) ans[i] = threadPath[i];
    *len = threadLen;
    delete(threadPath); delete(changePath);
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
    srand((unsigned int)time(NULL));
    int n, *x, *y;
    scanf("%d", &n);
    x = new int[n]; y = new int[n];
    for (int i = 0; i < n; i++) scanf("%d%d", &x[i], &y[i]);
    
    int *ans = new int[n];
    double *len = new double;
    
    // 调用函数并计时
    timeval t1, t2;
    gettimeofday(&t1, NULL);
    SA_TSP_Serial(x, y, n, ans, len);
    gettimeofday(&t2, NULL);
    
    // 输出最优结果
    printf("Time: %.4fs\n", (t2.tv_sec-t1.tv_sec+(t2.tv_usec-t1.tv_usec)/1.0e6));
    printf("Final result: \n  Path: ");
    for (int i = 0; i < n; i++) printf("%d -> ", ans[i]);
    printf("%d\n", ans[0]);
    printf("  Length: %8.2f\n\n", *len);
    delete[] x, delete[] y, delete[] ans, delete len;
}