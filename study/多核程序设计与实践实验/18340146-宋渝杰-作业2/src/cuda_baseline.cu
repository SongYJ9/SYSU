/*
#############################################################
##  姓名：宋渝杰
##  文件说明：cuda实验二的baseline版本程序
#############################################################
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

int sizex = 8, sizey = 8;                       // blocksize
int readInFlie = true, printMatrix = false;     // 是否从文件读入输入矩阵、是否输出矩阵

struct Matrix { // 矩阵结构体
    int x, y;
    double** v;
}; 

/*
#############################################################
##  函数：print
##  函数描述：按二维矩阵形式输出矩阵
##  参数描述：
##  Matrix *m：Matrix类型的结构体矩阵
#############################################################
*/

void print(Matrix* m) {
    for (int i = 0; i < m->x; i++) {
        for (int j = 0; j < m->y; j++) printf("%12.5f ", m->v[i][j]);
        printf("\n");
    }
}

/*
#############################################################
##  函数：cal
##  函数描述：核函数，计算输入矩阵a的熵，计算结果存在矩阵b里
##  参数描述：
##  Matrix *a：输入矩阵a
##  Matrix *b：结果矩阵b
#############################################################
*/

__global__ void cal(Matrix* a, Matrix* b) {
    int x = blockIdx.y * blockDim.y + threadIdx.y, y = blockIdx.x * blockDim.x + threadIdx.x;
    if (x < a->x && y < a->y) {
        int num[16] = {0}, sum = 0;
        double ans = 0;
        for (int i = max(x - 2, 0); i < min(x + 3, a->x); i++) {
            for (int j = max(y - 2, 0); j < min(y + 3, a->y); j++) {
                num[(int)(a->v[i][j])]++;
                sum++;
            }
        }
        for (int i = 0; i < 16; i++)
            if (num[i]) ans -= (double)num[i] / sum * log((double)num[i] / sum);
        b->v[x][y] = ans;
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
    Matrix *a, *b;
    cudaMallocManaged((void**)&a, sizeof(Matrix));
    cudaMallocManaged((void**)&b, sizeof(Matrix));
    scanf("%d%d", &a->x, &a->y);
    b->x = a->x; b->y = a->y;
    cudaMallocManaged((void**)&a->v, a->x * sizeof(double*));
    cudaMallocManaged((void**)&b->v, b->x * sizeof(double*));
    for (int i = 0; i < a->x; i++) {
        cudaMallocManaged((void**)&a->v[i], a->y * sizeof(double));
        cudaMallocManaged((void**)&b->v[i], b->y * sizeof(double));
    }
    for (int i = 0; i < a->x; i++)
        for (int j = 0; j < a->y; j++)
            scanf("%lf", &a->v[i][j]);
    
    // 设置线程块和网格大小
    dim3 block(sizex, sizey), grid(a->x / sizex + 1, a->y / sizey + 1);
    
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
        print(a);
        printf("\nMatrix b: \n");
        print(b); 
    }
    return 0;
}