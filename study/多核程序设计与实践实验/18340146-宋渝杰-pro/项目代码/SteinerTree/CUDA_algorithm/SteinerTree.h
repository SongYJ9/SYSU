/*
#############################################################
##  姓名：宋渝杰、黄思蓉
##  文件说明：cuda大作业“模拟退火解决最小斯坦纳树问题”CUDA程序头文件
#############################################################
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <algorithm>
#include <sys/time.h>
#include <curand_kernel.h>
#define blockSize 64
#define gridSize 2
#define Length 2
#define Tstart 1e2
#define Tend 1e-5

bool readInFlie = true;

/*
#############################################################
##  函数：SA_SteinerTree
##  函数描述：并行模拟退火算法解决最小斯坦纳树问题
##  参数描述：
##  int *map：节点之间的距离矩阵
##  int *key：关键节点序列
##  int n：节点个数
##  int k：关键节点个数
##  int *ans：返回最优线程的斯坦纳树节点序列
##  int *num：用于线程并行规约求最优线程的斯坦纳树节点个数
##  int *len：用于线程并行规约求最优线程的斯坦纳树边权和
##  int *index：用于线程并行规约求最优线程号
##  int seed：cpu传来的随机种子
#############################################################
*/

__global__ void SA_SteinerTree(int *map, int *key, int n, int k, int *ans, int *num, int *len, int *index, int seed) {
    
    // 初始化工作
    int threadId = blockIdx.x * blockDim.x + threadIdx.x;              // 计算线程ID
    int *threadKey = new int[k];
    int *threadSuperKey = new int[n], *ChangeSuperKey = new int[n];    // 线程本地内存
    int *vis = new int[n], *primLen = new int[n];
    int threadSuperKeySize = k, ChangeSuperKeySize = k;
    int threadLen = 1e6, changeLen = 1e6;
    double T = Tstart, alpha = 0.95;                                   // 模拟退火的温度和降温率
    int L = Length, way = 0, add, remove, judge;                       // 每个温度T的迭代次数，以及sa的辅助变量
    curandState state;
    curand_init(seed, threadId, 0, &state);
    for (int i = 0; i < k; i++) 
        threadKey[i] = threadSuperKey[i] = ChangeSuperKey[i] = key[i];
    
    // 降温迭代过程
    while (T > Tend) {
        if (ChangeSuperKeySize == n) way = 1;
        else if (ChangeSuperKeySize == k || (T < Tend * 5 && threadSuperKeySize <= threadLen)) way = 0;
        else way = curand(&state) % 3;
        
        if (way == 0) {                                                // 新增一个中间节点
            while (1) {
                add = curand(&state) % n;
                judge = 1;
                for (int i = 0; i < ChangeSuperKeySize; i++)
                    if (ChangeSuperKey[i] == add) judge = 0;
                if (judge == 1) break;
            }
            ChangeSuperKey[ChangeSuperKeySize++] = add;
        }
        else if (way == 1) {                                           // 删除一个中间节点
            while (1) {
                remove = curand(&state) % n;
                judge = 0;
                for (int i = 0; i < ChangeSuperKeySize; i++)
                    if (ChangeSuperKey[i] == remove) judge = 1;
                if (judge)
                    for (int i = 0; i < k; i++)
                        if (threadKey[i] == remove) judge = 0;
                if (judge) break;
            }
            for (int i = 0; i < ChangeSuperKeySize; i++)
                if (ChangeSuperKey[i] == remove) {
                    for (int j = i+1; j < ChangeSuperKeySize; j++)
                        ChangeSuperKey[j-1] = ChangeSuperKey[j];
                    break;
                }
            ChangeSuperKeySize--;
        }
        else {                                                         // 替换一个中间节点
            while (1) {
                add = curand(&state) % n;
                judge = 1;
                for (int i = 0; i < ChangeSuperKeySize; i++)
                    if (ChangeSuperKey[i] == add) judge = 0;
                if (judge == 1) break;
            }
            while (1) {
                remove = curand(&state) % n;
                judge = 0;
                for (int i = 0; i < ChangeSuperKeySize; i++)
                    if (ChangeSuperKey[i] == remove) judge = 1;
                if (judge && remove != add)
                    for (int i = 0; i < k; i++)
                        if (threadKey[i] == remove) judge = 0;
                if (judge) break;
            }
            for (int i = 0; i < ChangeSuperKeySize; i++)
                if (ChangeSuperKey[i] == remove) {
                    ChangeSuperKey[i] = add;
                    break;
                }
        }
        
        // prim算法计算最小生成树（最小斯坦纳树）边权和
        changeLen = 0;
        for (int i = 0; i < ChangeSuperKeySize; i++) {
            vis[i] = 0;
            primLen[i] = map[ChangeSuperKey[0] * n + ChangeSuperKey[i]];
        }
        vis[0] = 1;
        for (int i = 1; i < ChangeSuperKeySize; i++) {
            int mi = 1e9, index = -1;
            for (int j = 0; j < ChangeSuperKeySize; j++) {
                if (vis[j] == 0 && primLen[j] < mi) {
                    mi = primLen[j];
                    index = j;
                }
            }
            vis[index] = 1;
            changeLen += primLen[index];
            for (int j = 0; j < ChangeSuperKeySize; j++)
                if (map[ChangeSuperKey[j] * n + ChangeSuperKey[index]] < primLen[j])
                    primLen[j] = map[ChangeSuperKey[j] * n + ChangeSuperKey[index]];
        }
        
        // 如果变换后权值和更小，则接受本次变换，否则以一定概率接受本次变换
        if ((changeLen < threadLen || (changeLen == threadLen && ChangeSuperKeySize > threadSuperKeySize) || curand(&state) % 100 < exp(-(changeLen - threadLen + 1) / T) * 100)) {
            threadLen = changeLen;
            threadSuperKeySize = ChangeSuperKeySize;
            for (int i = 0; i < ChangeSuperKeySize; i++)
                threadSuperKey[i] = ChangeSuperKey[i];
        }
        else {
            ChangeSuperKeySize = threadSuperKeySize;
            for (int i = 0; i < threadSuperKeySize; i++)
                ChangeSuperKey[i] = threadSuperKey[i];
        }
        
        if (L-- == 0) {
            L = Length;
            T *= alpha;
        }
    }
    
    // 返回线程结果
    num[threadId] = threadSuperKeySize;
    len[threadId] = threadLen;
    index[threadId] = threadId;
    __syncthreads();
    
    // 并行规约找出线程块内最优结果
    for (int s = blockSize / 2; s > 0; s /= 2) {
        if (threadId % blockSize / s == 0) {
            if (len[threadId] > len[threadId + s] || (len[threadId] == len[threadId + s] && num[threadId] < num[threadId + s])) {
                num[threadId] = num[threadId + s];
                len[threadId] = len[threadId + s];
                index[threadId] = index[threadId + s];
            }
        }
        __syncthreads();
    }
    
    // 最优线程返回斯坦纳树节点序列等信息
    if (threadId == index[blockIdx.x * blockSize]) {
        for (int i = 0; i < threadSuperKeySize; i++) 
            ans[blockIdx.x * n + i] = threadSuperKey[i];
        num[blockIdx.x] = threadSuperKeySize;
        len[blockIdx.x] = threadLen;
        index[blockIdx.x] = threadId;
    }
    __syncthreads();
}


/*
    1. Prim函数优化

    #############################################################
    ##  函数：Prim
    ##  函数描述：使用Prim算法计算最小生成树边权和
    ##  参数描述：
    ##  int *map：城市的x坐标
    ##  int n：城市的y坐标
    ##  int *ChangeSuperKey：目前选出的最小生成树（最小斯坦纳树）的节点
    ##  int ChangeSuperKeySize：节点个数
    #############################################################

    __device__ int Prim(int *map, int n, int *ChangeSuperKey, int ChangeSuperKeySize) {
        int ans = 0, *vis = new int[ChangeSuperKeySize], *len = new int[ChangeSuperKeySize];
        for (int i = 0; i < ChangeSuperKeySize; i++) {
            vis[i] = 0;
            len[i] = map[ChangeSuperKey[0] * n + ChangeSuperKey[i]];
        }
        vis[0] = 1;
        for (int i = 1; i < ChangeSuperKeySize; i++) {
            int mi = 1e9, index = -1;
            for (int j = 0; j < ChangeSuperKeySize; j++) {
                if (vis[j] == 0 && len[j] < mi) {
                    mi = len[j];
                    index = j;
                }
            }
            vis[index] = 1;
            ans += len[index];
            for (int j = 0; j < ChangeSuperKeySize; j++)
                if (map[ChangeSuperKey[j] * n + ChangeSuperKey[index]] < len[j])
                    len[j] = map[ChangeSuperKey[j] * n + ChangeSuperKey[index]];
        }
        delete[] vis, delete[] len;
        return ans;
    }
    
    // changeLen = Prim(map, n, ChangeSuperKey, ChangeSuperKeySize);

*/