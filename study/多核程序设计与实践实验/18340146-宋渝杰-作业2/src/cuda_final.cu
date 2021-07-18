/*
#############################################################
##  姓名：宋渝杰
##  文件说明：cuda实验二的最终优化版本程序
#############################################################
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

short sizex = 256, sizey = 4;                   // blocksize
__constant__ short X, Y;                        // 常量内存存储矩阵高和宽
int readInFlie = true, printMatrix = false;     // 是否从文件读入输入矩阵、是否输出矩阵

/*
#############################################################
##  函数：print
##  函数描述：按二维矩阵形式输出矩阵（short类型和float类型）
##  参数描述：
##  T *m：类型为T的一维矩阵
##  int X：矩阵的高
##  int Y：矩阵的宽
#############################################################
*/

template<class T>
void print(T *m, int X, int Y) {
    for (int i = 0; i < X; i++) {
        for (int j = 0; j < Y; j++) printf("%12.5f ", (float)m[i * Y + j]); // 保留五位小数输出
        printf("\n");
    }
}

/*
#############################################################
##  函数：cal
##  函数描述：核函数，计算输入矩阵a的熵，计算结果存在矩阵b里
##  参数描述：
##  short *a：输入矩阵a
##  float *b：结果矩阵b
#############################################################
*/

__global__ void cal(short *a, float *b) {
    short x = blockIdx.y * blockDim.y + threadIdx.y, y = blockIdx.x * blockDim.x + threadIdx.x; // 定位线程id
    if (x < X && y < Y) {
        short num[16] = {0}, sum = 0;   // 记录0-15数值的数量、窗口实际大小
        float ans = 0;                  // 记录这个位置熵的结果
        __shared__ float loge[26];      // log共享内存打表
        loge[0] = 0.0; loge[1] = 0.0; loge[2] = 0.693147; loge[3] = 1.098612; loge[4] = 1.386294; loge[5] = 1.609437;
        loge[6] = 1.791759; loge[7] = 1.945910; loge[8] = 2.079441; loge[9] = 2.197224; loge[10] = 2.302585;
        loge[11] = 2.397895; loge[12] = 2.484906; loge[13] = 2.564949; loge[14] = 2.639057; loge[15] = 2.708050;
        loge[16] = 2.772588; loge[17] = 2.833213; loge[18] = 2.890371; loge[19] = 2.944438; loge[20] = 2.995732;
        loge[21] = 3.044522; loge[22] = 3.091042; loge[23] = 3.135494; loge[24] = 3.178053; loge[25] = 3.218875;
        for (short i = max(x - 2, 0); i < min(x + 3, X); i++) {
            for (short j = max(y - 2, 0); j < min(y + 3, Y); j++) {
                num[a[i * Y + j]]++;    // 该数值数量+1
                sum++;                  // 窗口实际大小+1
            }
        }
        for (short i = 0; i < 16; i++)  // 计算熵（按照熵的计算公式计算）
            if (num[i]) ans -= (float)num[i] / sum * (loge[num[i]] - loge[sum]);
        b[x * Y + y] = ans;
    }
}

/*
#############################################################
##  函数：main
##  函数描述：程序主函数，负责读入矩阵、申请内存、调用核函数、输出计算时间和矩阵等工作
##  参数描述：
##  int argc, char* argv[]：可变输入参数，实际上只接受第一个输入，即输入文件名
#############################################################
*/

int main(int argc, char* argv[]) {

    // 读入输入矩阵、申请内存
    if (readInFlie) freopen(argv[1], "r", stdin);
    short x, y, *a;
    float *b;
    scanf("%d%d", &x, &y);
    cudaMallocManaged((void**)&a, x * y * sizeof(short));
    cudaMallocManaged((void**)&b, x * y * sizeof(float));
    for (short i = 0; i < x; i++)
        for (short j = 0; j < y; j++)
            scanf("%hd", &a[i * y + j]);
    cudaMemcpyToSymbol(X, &x, sizeof(short));
    cudaMemcpyToSymbol(Y, &y, sizeof(short)); 
    
    // 设置线程块和网格大小
    dim3 block(sizex, sizey), grid(x / sizex + 1, y / sizey + 1);
    
    // 调用核函数并计时
    timeval t1, t2;
    gettimeofday(&t1, NULL);
    cal <<< grid, block >>> (a, b);
    cudaDeviceSynchronize();
    gettimeofday(&t2, NULL);
    
    // 输出结果矩阵
    printf("Time: %.4fs\n", (t2.tv_sec-t1.tv_sec+(t2.tv_usec-t1.tv_usec)/1.0e6));
    if (printMatrix) {
        printf("Matrix a: \n");
        print(a, x, y);
        printf("\nMatrix b: \n");
        print(b, x, y);
    }
    return 0;
}