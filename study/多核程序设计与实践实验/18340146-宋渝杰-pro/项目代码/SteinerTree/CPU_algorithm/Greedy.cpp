/*
#############################################################
##  姓名：宋渝杰、黄思蓉
##  文件说明：cuda大作业“最小斯坦纳树问题”cpu贪心算法程序
#############################################################
*/

#include <iostream>
#include <algorithm>
#include <cstring>
#include <sys/time.h>
#define ll long long
using namespace std;

int n, m, k;
int dis[305][305], vis[305], p[305];
bool readInFlie = true;

/*
#############################################################
##  函数：Greedy
##  函数描述：通过Prim算法求最小生成树权值和
##  参数描述：无参数
#############################################################
*/

int Greedy() {
    // floyd算法预处理多源最短路径
    for (int l = 0; l < n; l++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                dis[i][j] = min(dis[i][j], dis[i][l] + dis[l][j]);
    // prim算法
    int ans = 0, prim[k], index;
    for (int i = 0; i < k; i++) prim[i] = dis[p[0]][p[i]];
    vis[p[0]] = 1;
    for (int i = 1; i < k; i++) {
        index = -1;
        for (int j = 0; j < k; j++)
            if (vis[p[j]] == 0 and (index == -1 or prim[j] < prim[index]))
                index = j;
        vis[p[index]] = 1;
        ans += prim[index];
        for (int j = 0; j < k; j++) 
            prim[j] = min(prim[j], dis[p[j]][p[index]]);
    }
    return ans;
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
    int ans = Greedy();
    gettimeofday(&t2, NULL);
    
    // 输出最优结果
    printf("Time: %.6fs\n", (t2.tv_sec-t1.tv_sec+(t2.tv_usec-t1.tv_usec)/1.0e6));
    printf("Length: %d\n\n", ans);
}

