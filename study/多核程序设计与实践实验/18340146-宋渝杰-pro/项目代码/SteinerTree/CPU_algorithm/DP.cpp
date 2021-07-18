/*
#############################################################
##  姓名：宋渝杰、黄思蓉
##  文件说明：cuda大作业“最小斯坦纳树问题”cpu DP算法程序
#############################################################
*/

#include <iostream>
#include <algorithm>
#include <cstring>
#include <sys/time.h>
#define ll long long
using namespace std;

int n, m, k;
int dis[105][105], dp[1<<15][105], vis[105], p[105];
bool readInFlie = true;

/*
#############################################################
##  函数：dij
##  函数描述：通过Dijkstra算法求最短路思想对DP数组进行松弛，辅助DP算法工作
##  参数描述：
##  int s：对点集s相关DP数组进行松弛
#############################################################
*/

void dij(int s) { // Dijkstra松弛
    for (int i = 0; i < n; i++) vis[i] = 0;
    for (int i = 0; i < n; i++) {
        int index = -1;
        for (int j = 0; j < n; j++)
            if (vis[j] == 0 and (index == -1 or dp[s][j] < dp[s][index]))
                index = j;
        vis[index] = 1;
        for (int j = 0; j < n; j++)
            dp[s][j] = min(dp[s][j], dp[s][index] + dis[j][index]);
    }
}

/*
#############################################################
##  函数：SteinerTree
##  函数描述：通过状态压缩DP算法求最小斯坦纳树精确解
##  参数描述：无参数
#############################################################
*/

int SteinerTree() {
    // floyd算法预处理多源最短路径
    for (int l = 0; l < n; l++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                dis[i][j] = min(dis[i][j], dis[i][l] + dis[l][j]);
    
    // 状态压缩DP转移
    for (int i = 1; i < (1 << k); i++) {
        for (int j = i; j > 0; j = (j - 1) & i)
            for (int l = 0; l < n; l++)
                dp[i][l] = min(dp[i][l], dp[j][l] + dp[i-j][l]);
        if ((i&(i-1)) == 0) {
            for (int j = 0; j < k; j++) {
                if ((i&(1<<j)) > 0) {
                    dp[i][p[j]] = 0;
                    break;
                }
            }
        }
        dij(i);
    }
    
    // 寻找最优解
    int mi = 1e9;
    for (int i = 0; i < n; i++) mi = min(mi, dp[(1<<k)-1][i]);
    return mi;
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
    scanf("%d%d%d", &n, &m, &k);
    memset(dis, 0x3f, sizeof(dis));
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 0; i < n; i++) dis[i][i] = 0;
    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        dis[x][y] = dis[y][x] = 1;
    }
    for (int i = 0; i < k; i++) scanf("%d", &p[i]);
    
    // 调用函数并计时
    timeval t1, t2;
    gettimeofday(&t1, NULL);
    int ans = SteinerTree();
    gettimeofday(&t2, NULL);
    
    // 输出最优结果
    printf("Time: %.6fs\n", (t2.tv_sec-t1.tv_sec+(t2.tv_usec-t1.tv_usec)/1.0e6));
    printf("Length: %d\n\n", ans);
}

