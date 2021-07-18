/*
#############################################################
##  姓名：宋渝杰
##  文件说明：cuda实验二的openmp版本程序
#############################################################
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>
#include <algorithm>
using namespace std;

int X, Y;                                         // 矩阵大小
int readInFlie = true, printMatrix = false;       // 是否从文件读入输入矩阵、是否输出矩阵

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
        for (int j = 0; j < Y; j++) printf("%12.5f ", (float)m[i * Y + j]);
        printf("\n");
    }
}

/*
#############################################################
##  函数：cal
##  函数描述：openmp并行程序，计算输入矩阵a的熵，计算结果存在矩阵b里
##  参数描述：
##  short *a：输入矩阵a
##  float *b：结果矩阵b
#############################################################
*/

void cal(short* a, float* b) {
    #pragma omp parallel for num_threads(12)
    for (short x = 0; x < X; x++) {
        for (short y = 0; y < Y; y++) {
            short num[16] = {0}, sum = 0;
            float ans = 0, loge[26];
            loge[0] = loge[1] = 0.0; loge[2] = 0.693147; loge[3] = 1.098612; loge[4] = 1.386294; loge[5] = 1.609437;
            loge[6] = 1.791759; loge[7] = 1.945910; loge[8] = 2.079441; loge[9] = 2.197224; loge[10] = 2.302585;
            loge[11] = 2.397895; loge[12] = 2.484906; loge[13] = 2.564949; loge[14] = 2.639057; loge[15] = 2.708050;
            loge[16] = 2.772588; loge[17] = 2.833213; loge[18] = 2.890371; loge[19] = 2.944438; loge[20] = 2.995732;
            loge[21] = 3.044522; loge[22] = 3.091042; loge[23] = 3.135494; loge[24] = 3.178053; loge[25] = 3.218875;
            for (short i = max(x - 2, 0); i < min(x + 3, X); i++) {
                for (short j = max(y - 2, 0); j < min(y + 3, Y); j++) {
                    num[a[i * Y + j]]++;
                    sum++;
                }
            }
            for (short i = 0; i < 16; i++)
                if (num[i]) ans -= (float)num[i] / sum * (loge[num[i]] - loge[sum]);
            b[x * Y + y] = ans;
        }
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
    scanf("%d%d", &X, &Y);
    short *a = (short*)malloc(X * Y * sizeof(short));
    float *b = (float*)malloc(X * Y * sizeof(float));
    for (short i = 0; i < X; i++)
        for (short j = 0; j < Y; j++)
            scanf("%hd", &a[i * Y + j]);
    
    // 调用openmp并行函数并计时
    timeval t1, t2;
    gettimeofday(&t1, NULL);
    cal(a, b);
    gettimeofday(&t2, NULL);
    
    // 输出结果矩阵
    printf("Time: %.4fs\n", (t2.tv_sec-t1.tv_sec+(t2.tv_usec-t1.tv_usec)/1.0e6));
    if (printMatrix) {
        printf("Matrix a: \n");
        print(a, X, Y);
        printf("\nMatrix b: \n");
        print(b, X, Y);
    }
    return 0;
}