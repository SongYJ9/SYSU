/*
#############################################################
##  姓名：宋渝杰、黄思蓉
##  文件说明：cuda大作业“模拟退火解决TSP问题”final版本程序
#############################################################
*/

#include "TSP_final.h"

/*
#############################################################
##  函数：main
##  函数描述：主函数，负责文件输入、内存申请、调用核函数、输出最优结果。
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
    
    // 申请cuda内存
    int GPU_num;
    cudaGetDeviceCount(&GPU_num);
    int *ans[GPU_num], *index[GPU_num], *d_x[GPU_num], *d_y[GPU_num], *d_ans[GPU_num], *d_index[GPU_num];
    double *len[GPU_num], *d_len[GPU_num];
    cudaStream_t stream[GPU_num];
    for (int i = 0; i < GPU_num; i++) {
        cudaSetDevice(i);
        ans[i] = new int[n * gridSize];
        index[i] = new int[gridSize];
        len[i] = new double[gridSize];
        cudaMalloc((void**)&d_x[i], n * sizeof(int));
        cudaMalloc((void**)&d_y[i], n * sizeof(int));
        cudaMalloc((void**)&d_ans[i], n * gridSize * sizeof(int));
        cudaMalloc((void**)&d_index[i], blockSize * gridSize * sizeof(int));
        cudaMalloc((void**)&d_len[i], blockSize * gridSize * sizeof(double));
        cudaStreamCreate(&stream[i]);
    }

    // 设置线程块和网格大小
    dim3 block(blockSize), grid(gridSize);
    
    // openmp+cuda 调用核函数并计时
    timeval t1, t2;
    gettimeofday(&t1, NULL);
    #pragma omp parallel for num_threads(GPU_num)
    for (int i = 0; i < GPU_num; i++) {
        cudaSetDevice(i);
        cudaMemcpyAsync(d_x[i], x, n * sizeof(int), cudaMemcpyHostToDevice, stream[i]);
        cudaMemcpyAsync(d_y[i], y, n * sizeof(int), cudaMemcpyHostToDevice, stream[i]);
        SA_TSP <<< grid, block, 0, stream[i]>>> (d_x[i], d_y[i], n, d_ans[i], d_len[i], d_index[i], rand());
        cudaMemcpyAsync(ans[i], d_ans[i], n * gridSize * sizeof(int), cudaMemcpyDeviceToHost, stream[i]);
        cudaMemcpyAsync(len[i], d_len[i], gridSize * sizeof(double), cudaMemcpyDeviceToHost, stream[i]);
        cudaMemcpyAsync(index[i], d_index[i], gridSize * sizeof(int), cudaMemcpyDeviceToHost, stream[i]);
    }
    gettimeofday(&t2, NULL);
    
    // cuda内存释放
    for (int i = 0; i < GPU_num; i++) {
        cudaSetDevice(i);
        cudaStreamSynchronize(stream[i]);
        cudaFree(d_x[i]); cudaFree(d_y[i]); 
        cudaFree(d_ans[i]); cudaFree(d_len[i]); cudaFree(d_index[i]);
        cudaStreamDestroy(stream[i]);
    }
    
    // 计算最优结果
    double mi = 1e18;
    int GPUIndex = -1, gridIndex = -1;
    for (int i = 0; i < GPU_num; i++) {
        for (int j = 0; j < gridSize; j++) {
            if (len[i][j] < mi) {
                mi = len[i][j];
                GPUIndex = i; gridIndex = j;
            }
        }
    }
    
    // 输出最优结果
    printf("Time: %.4fs\n", (t2.tv_sec-t1.tv_sec+(t2.tv_usec-t1.tv_usec)/1.0e6));
    printf("Final result: \n  GPU_index: %d\n  thread_index: %d \n  Path: ", GPUIndex, index[GPUIndex][gridIndex]);
    for (int i = 0; i < n; i++) printf("%d -> ", ans[GPUIndex][gridIndex * n + i]);
    printf("%d\n", ans[GPUIndex][gridIndex * n]);
    printf("  Length: %8.2f\n\n", len[GPUIndex][gridIndex]);
    
    // 文件写入
    freopen("../out/out.txt", "w", stdout);
    for (int i = 0; i < n; i++) printf("%d ", ans[GPUIndex][gridIndex * n + i]);
    
    // host内存释放
    delete[] x; delete[] y; 
    for (int i = 0; i < GPU_num; i++) {
        delete[] ans[i]; 
        delete[] len[i]; 
        delete[] index[i]; 
    }
    
    return 0;
}