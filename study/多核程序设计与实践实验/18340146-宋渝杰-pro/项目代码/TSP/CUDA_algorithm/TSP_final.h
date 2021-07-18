/*
#############################################################
##  姓名：宋渝杰、黄思蓉
##  文件说明：cuda大作业“模拟退火解决TSP问题”final版本程序头文件
#############################################################
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <curand_kernel.h>
#include <sys/time.h>
#include <omp.h>
#define blockSize 128
#define gridSize 2
#define Length 10
#define Tstart 1e4
#define Tend 1e-6

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

__device__ double dis(int X_x, int X_y, int Y_x, int Y_y) {
    return sqrt(pow(X_x - Y_x, 2) + pow(X_y - Y_y, 2));
}

/*
#############################################################
##  函数：SA_TSP
##  函数描述：并行模拟退火算法解决TSP问题
##  参数描述：
##  int *x：城市的x坐标
##  int *y：城市的y坐标
##  int n：城市个数
##  int *path：返回最优线程的回路路径
##  double *len：用于线程并行规约求最优长度
##  int *index：用于线程并行规约求最优线程号
##  int seed：cpu传来的随机种子
#############################################################
*/

__global__ void SA_TSP(int *x, int *y, int n, int *ans, double *len, int *index, int seed) {

    // 初始化工作
    int threadId = blockIdx.x * blockDim.x + threadIdx.x;              // 计算线程ID
    int *threadPath = new int[n], *changePath = new int[n+1];          // 线程计算的回路路线
    double threadLen = 0, delta = 0;                                   // 线程计算的回路长度
    double T = Tstart, alpha = 0.95;                                   // 模拟退火的温度和降温率
    int L = Length, way = 0, t1, t2, mid, r;                           // 每个温度T的迭代次数，以及sa的辅助变量
    curandState state;
    curand_init(seed, threadId, 0, &state);                            // 核函数随机函数
    for (int i = 0; i < n; i++) changePath[i] = threadPath[i] = i;     // 初始化为0->1->...->n-1->0的回路
    changePath[n] = 0;
    for (int i = 0; i < n; i++) 
        threadLen += dis(x[i], y[i], x[(i+1)%n], y[(i+1)%n]);          // 计算初始回路长度
                         
    // 降温迭代过程
    while (T > Tend) {
        if (way == 0) {                                                // 交换相邻的t1、t2两个点
            t1 = curand(&state) % (n - 2) + 1;
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
                t1 = curand(&state) % (n - 1) + 1;
                t2 = curand(&state) % (n - 1) + 1;
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
                t1 = curand(&state) % (n - 1) + 1;
                t2 = curand(&state) % (n - 1) + 1;
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
                mid = curand(&state) % n;
                r = curand(&state) % 10;
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
        if (delta < 0 || curand(&state) % 100 < exp(-delta / T) * 100) {
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
    
    // 返回线程结果
    len[threadId] = threadLen;
    index[threadId] = threadId;
    __syncthreads();
    
    // 并行规约找出线程块内最优结果
    for (int s = blockSize / 2; s > 0; s /= 2) {
        if (threadId % blockSize < s) {
            if (len[threadId] > len[threadId + s]) {
                len[threadId] = len[threadId + s];
                index[threadId] = index[threadId + s];
            }
        }
        __syncthreads();
    }
    
    // 最优线程返回路径等信息
    if (threadId == index[blockIdx.x * blockSize]) {
        for (int i = 0; i < n; i++) ans[i + blockIdx.x * n] = threadPath[i];
        len[blockIdx.x] = threadLen;
        index[blockIdx.x] = threadId;
    }
    __syncthreads();
    delete[] threadPath; delete[] changePath;
}