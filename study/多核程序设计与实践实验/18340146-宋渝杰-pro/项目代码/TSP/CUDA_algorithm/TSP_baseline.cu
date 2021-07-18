/*
#############################################################
##  姓名：宋渝杰、黄思蓉
##  文件说明：cuda大作业“模拟退火解决TSP问题”baseline版本程序
#############################################################
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <curand_kernel.h>
#include <sys/time.h>

short blocksize = 512;
bool readInFlie = true;

/*
#############################################################
##  函数：SA_TSP
##  函数描述：并行模拟退火算法解决TSP问题
##  参数描述：
##  int *x：城市的x坐标
##  int *y：城市的y坐标
##  int n：城市个数
##  int *path：返回每个线程的回路路径
##  double *len：返回每个线程的回路长度
##  int seed：cpu传来的随机种子
#############################################################
*/

__global__ void SA_TSP(int *x, int *y, int n, int *path, double *len, int seed) {

    // 初始化工作
    int threadId = blockIdx.x * blockDim.x + threadIdx.x;              // 计算线程ID
    int *threadPath = new int[n], *changePath = new int[n];            // 线程计算的回路路线
    double threadLen = 1e18, changeLen = 0;                            // 线程计算的回路长度
    double T = 1e3, alpha = 0.95;                                      // 模拟退火的温度和降温率
    int L = 10;
    curandState state;
    curand_init(seed, threadId, 0, &state);                            // 核函数随机函数
    for (int i = 0; i < n; i++) changePath[i] = i;                     // 初始化为1->2->...->n->1的回路
    
    // 降温迭代过程
    while (T > 1e-3) {
        int random = curand(&state) % 100;                             // 随机变换
        if (random < 20) {
            int t1 = curand(&state) % (n - 1);
            int t2 = t1 + 1;
            int temp = changePath[t1]; 
            changePath[t1] = changePath[t2]; 
            changePath[t2] = temp;                                     // 交换相邻的两个点
        }
        else if (random < 40) {
            int t1, t2;
            do {
                t1 = curand(&state) % n;
                t2 = curand(&state) % n;
            } while (t1 >= t2);
            int temp = changePath[t1];
            changePath[t1] = changePath[t2];
            changePath[t2] = temp;                                     // 交换任意的两个点
        }
        else if (random < 70) {
            int t1, t2;
            do {
                t1 = curand(&state) % n;
                t2 = curand(&state) % n;
            } while (t1 >= t2);
            for (int i = t1, j = t2; i < j; i++, j--) {
                int temp = changePath[i];
                changePath[i] = changePath[j];
                changePath[j] = temp;                                  // 翻转[t1, t2]序列
            }
        }
        else {
            int t1, t2;
            do {
                t1 = curand(&state) % n;
                t2 = curand(&state) % (n / 3);
            } while (t1 - t2 < 0 || t1 + t2 >= n);
            for (int i = t1 - t2, j = t1; i < t1; i++, j++) {
                int temp = changePath[i];
                changePath[i] = changePath[j];
                changePath[j] = temp;                                  // 交换[t1-t2, t1)和[t1, t1+t2)序列
            }
        }
        
        // 计算变换后的回路长度
        changeLen = 0;
        for (int i = 1; i < n; i++) 
            changeLen += sqrt(pow(x[changePath[i]] - x[changePath[i-1]], 2)
                + pow(y[changePath[i]] - y[changePath[i-1]], 2));
        changeLen += sqrt(pow(x[changePath[n-1]] - x[changePath[0]], 2)
                + pow(y[changePath[n-1]] - y[changePath[0]], 2));
        
        // 如果变换后回路更优，则接受本次变换，否则以一定概率接受本次变换
        if (changeLen < threadLen || curand(&state) % 100 < exp(-(changeLen - threadLen)/T) * 100) {
            threadLen = changeLen;
            for (int i = 0; i < n; i++) threadPath[i] = changePath[i];
        }
        else {
            for (int i = 0; i < n; i++) changePath[i] = threadPath[i];
        }
        
        // 迭代次数足够后，进行温度下降
        if (L-- == 0) {
            L = 10;
            T *= alpha;
        }
    }
    
    // 返回线程结果
    for (int i = 0; i < n; i++) path[threadId * n + i] = threadPath[i];
    len[threadId] = threadLen;
    delete(threadPath); delete(changePath);
}

/*
#############################################################
##  函数：main
##  函数描述：主函数，负责文件输入、内存申请、调用核函数、计算最优结果并输出。
##  参数描述：
##  int argc, char* argv[]：可变输入参数，实际上只接受第一个输入，即输入文件名
#############################################################
*/

int main(int argc, char* argv[]) {

    cudaSetDevice(2);
    // 读入城市位置、申请内存
    if (readInFlie) freopen(argv[1], "r", stdin);
    srand((unsigned int)time(NULL));
    int n, *x, *y, *ans;
    double *len;
    scanf("%d", &n);
    cudaMallocManaged((void**)&x, n * sizeof(int));
    cudaMallocManaged((void**)&y, n * sizeof(int));
    cudaMallocManaged((void**)&ans, blocksize * n * sizeof(int));
    cudaMallocManaged((void**)&len, blocksize * sizeof(double));
    for (int i = 0; i < n; i++) scanf("%d%d", &x[i], &y[i]);

    // 设置线程块和网格大小
    dim3 block(blocksize), grid(1);
    
    // 调用核函数并计时
    timeval t1, t2;
    gettimeofday(&t1, NULL);
    SA_TSP <<< grid, block >>> (x, y, n, ans, len, rand());
    cudaDeviceSynchronize();
    gettimeofday(&t2, NULL);
    
    // 计算最优结果
    double mi = 1e18; int index = -1;
    for (int i = 0; i < blocksize; i++) {
        if (len[i] < mi) {
            mi = len[i];
            index = i;
        }
    }
    
    // 输出最优结果
    printf("Time: %.4fs\n", (t2.tv_sec-t1.tv_sec+(t2.tv_usec-t1.tv_usec)/1.0e6));
    printf("Final result: %d \nPath: ", index);
    for (int i = 0; i < n; i++) printf("%d -> ", ans[index * n + i]);
    printf("%d\n", ans[index * n]);
    printf("Length: %8.2f\n\n", len[index]);
    
    return 0;
}