/*
#############################################################
##  姓名：宋渝杰、黄思蓉
##  文件说明：cuda大作业“模拟退火解决最小斯坦纳树问题”CPU单线程模拟退火算法程序
#############################################################
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <algorithm>
#include <sys/time.h>
#define Length 1000
#define Tstart 1e4
#define Tend 1e-6

bool readInFlie = true;

/*
#############################################################
##  函数：SA_SteinerTree_Serial
##  函数描述：串行模拟退火算法解决最小斯坦纳树问题
##  参数描述：
##  int *map：节点之间的距离矩阵
##  int *key：关键节点序列
##  int n：节点个数
##  int k：关键节点个数
##  int *ans：返回最优斯坦纳树节点序列
##  int *num：返回最优斯坦纳树节点个数
##  int *len：返回最优斯坦纳树节点边权和
#############################################################
*/

void SA_SteinerTree_Serial(int *map, int *key, int n, int k, int *ans, int *num, int *len) {
    
    // 初始化工作
    long long count = 0;
    int *threadKey = new int[k];
    int *threadSuperKey = new int[n], *ChangeSuperKey = new int[n];    // 线程本地内存
    int *vis = new int[n], *primLen = new int[n];
    int threadSuperKeySize = k, ChangeSuperKeySize = k;
    int threadLen = 1e6, changeLen = 1e6;
    double T = Tstart, alpha = 0.95;                                   // 模拟退火的温度和降温率
    int L = Length, way = 0, add, remove, judge;                       // 每个温度T的迭代次数，以及sa的辅助变量
    for (int i = 0; i < k; i++) 
        threadKey[i] = threadSuperKey[i] = ChangeSuperKey[i] = key[i];
    
    // 降温迭代过程
    while (T > Tend) {
        count++;
        if (ChangeSuperKeySize == n) way = 1;
        else if (ChangeSuperKeySize == k || (T < Tend * 5 && threadSuperKeySize <= threadLen)) way = 0;
        else way = rand() % 3;
        
        if (way == 0) {                                                // 新增一个中间节点
            while (1) {
                add = rand() % n;
                judge = 1;
                for (int i = 0; i < ChangeSuperKeySize; i++)
                    if (ChangeSuperKey[i] == add) judge = 0;
                if (judge == 1) break;
            }
            ChangeSuperKey[ChangeSuperKeySize++] = add;
        }
        else if (way == 1) {                                           // 删除一个中间节点
            while (1) {
                remove = rand() % n;
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
                add = rand() % n;
                judge = 1;
                for (int i = 0; i < ChangeSuperKeySize; i++)
                    if (ChangeSuperKey[i] == add) judge = 0;
                if (judge == 1) break;
            }
            while (1) {
                remove = rand() % n;
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
        if ((changeLen < threadLen || (changeLen == threadLen && ChangeSuperKeySize > threadSuperKeySize) || rand() % 100 < exp(-(changeLen - threadLen + 1) / T) * 100)) {
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
    
    printf("count: %lld\n", count);  
    for (int i = 0; i < threadSuperKeySize; i++) 
        ans[i] = threadSuperKey[i];
    *num = threadSuperKeySize;
    *len = threadLen;
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

    // 读入无向连通图
    if (readInFlie) freopen(argv[1], "r", stdin);
    srand((unsigned int)time(NULL));
    int n, m, k, x, y;
    scanf("%d%d%d", &n, &m, &k);
    int *map = new int[n * n], *key = new int[k];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) 
            map[i * n + j] = (i == j ? 0 : 1e6);
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &x, &y);
        map[x * n + y] = map[y * n + x] = 1;
    }
    for (int i = 0; i < k; i++) scanf("%d", &key[i]);
    
    // floyd算法预处理多源最短路径
    for (int l = 0; l < n; l++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (map[i * n + j] > map[i * n + l] + map[l * n + j])
                    map[i * n + j] = map[i * n + l] + map[l * n + j];
    
    int *ans = new int[n], *num = new int, *len = new int;
    
    // 调用函数并计时
    timeval t1, t2;
    gettimeofday(&t1, NULL);
    SA_SteinerTree_Serial(map, key, n, k, ans, num, len);
    gettimeofday(&t2, NULL);
    
    // 输出最优结果
    printf("Time: %.4fs\n", (t2.tv_sec-t1.tv_sec+(t2.tv_usec-t1.tv_usec)/1.0e6));
    printf("TreeNodes: ");
    int lis[*num];
    for (int i = 0; i < *num; i++) lis[i] = ans[i];
    std::sort(lis, lis+(*num));
    for (int i = 0; i < *num; i++) printf("%d ", lis[i]);
    printf("\nNode_num: %d  Length: %d\n\n", *num, *len);
    delete[] map, delete[] key, delete[] ans, delete num, delete len;
}