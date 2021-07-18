/*
#############################################################
##  姓名：宋渝杰、黄思蓉
##  文件说明：cuda大作业“模拟退火解决最小斯坦纳树问题”CUDA程序
#############################################################
*/

#include "SteinerTree.h"

/*
#############################################################
##  函数：main
##  函数描述：主函数，负责文件输入、内存申请、调用核函数、输出最优结果。
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
                    
    // 申请cuda内存
    int GPU_num;
    cudaGetDeviceCount(&GPU_num);
    int *d_map[GPU_num], *d_key[GPU_num];
    int *ans[GPU_num], *num[GPU_num], *len[GPU_num], *index[GPU_num];
    int *d_ans[GPU_num], *d_num[GPU_num], *d_len[GPU_num], *d_index[GPU_num];
    cudaStream_t stream[GPU_num];
    for (int i = 0; i < GPU_num; i++) {
        cudaSetDevice(i);
        ans[i] = new int[n * gridSize];
        num[i] = new int[gridSize];
        len[i] = new int[gridSize];
        index[i] = new int[gridSize];
        cudaMalloc((void**)&d_map[i], n * n * sizeof(int));
        cudaMalloc((void**)&d_key[i], k * sizeof(int));
        cudaMalloc((void**)&d_ans[i], n * gridSize * sizeof(int));
        cudaMalloc((void**)&d_num[i], blockSize * gridSize * sizeof(int));
        cudaMalloc((void**)&d_len[i], blockSize * gridSize * sizeof(int));
        cudaMalloc((void**)&d_index[i], blockSize * gridSize * sizeof(int));
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
        cudaMemcpyAsync(d_map[i], map, n * n * sizeof(int), cudaMemcpyHostToDevice, stream[i]);
        cudaMemcpyAsync(d_key[i], key, k * sizeof(int), cudaMemcpyHostToDevice, stream[i]);
        SA_SteinerTree <<< grid, block, 0, stream[i]>>> (d_map[i], d_key[i], n, k, d_ans[i], d_num[i], d_len[i], d_index[i], rand());
        cudaMemcpyAsync(ans[i], d_ans[i], n * gridSize * sizeof(int), cudaMemcpyDeviceToHost, stream[i]);
        cudaMemcpyAsync(num[i], d_num[i], gridSize * sizeof(int), cudaMemcpyDeviceToHost, stream[i]);
        cudaMemcpyAsync(len[i], d_len[i], gridSize * sizeof(int), cudaMemcpyDeviceToHost, stream[i]);
        cudaMemcpyAsync(index[i], d_index[i], gridSize * sizeof(int), cudaMemcpyDeviceToHost, stream[i]);
    }
    gettimeofday(&t2, NULL);
    
    // cuda内存释放
    for (int i = 0; i < GPU_num; i++) {
        cudaSetDevice(i);
        cudaStreamSynchronize(stream[i]);
        cudaFree(d_map[i]); cudaFree(d_key[i]);
        cudaFree(d_ans[i]); cudaFree(d_num[i]); cudaFree(d_len[i]); cudaFree(d_index[i]);
        cudaStreamDestroy(stream[i]);
    }
    
    // 计算最优结果
    int mi = 1e6, c = 0, GPUIndex = -1, gridIndex = -1;
    for (int i = 0; i < GPU_num; i++) {
        for (int j = 0; j < gridSize; j++) {
            if (len[i][j] < mi || (len[i][j] == mi && num[i][j] > c)) {
                mi = len[i][j];
                c = num[i][j];
                GPUIndex = i; gridIndex = j;
            }
        }
    }
    
    // 输出最优结果
    printf("Time: %.4fs\n", (t2.tv_sec-t1.tv_sec+(t2.tv_usec-t1.tv_usec)/1.0e6));
    printf("Final result: \n  GPU_index: %d  thread_index: %d \n  TreeNodes: ", GPUIndex, index[GPUIndex][gridIndex]);
    int lis[num[GPUIndex][gridIndex]];
    for (int i = 0; i < num[GPUIndex][gridIndex]; i++) lis[i] = ans[GPUIndex][gridIndex*n+i];
    std::sort(lis, lis+num[GPUIndex][gridIndex]);
    for (int i = 0; i < num[GPUIndex][gridIndex]; i++) printf("%d ", lis[i]);
    printf("\n  Node_num: %d  Length: %d\n\n", num[GPUIndex][gridIndex], len[GPUIndex][gridIndex]);
    
    // 文件写入
    freopen("../out/out.txt", "w", stdout);
    for (int i = 0; i < num[GPUIndex][gridIndex]; i++) printf("%d ", lis[i]);
    
    // host内存释放
    delete[] map; delete[] key;
    for (int i = 0; i < GPU_num; i++) {
        delete[] ans[i];
        delete[] num[i];
        delete[] len[i];
        delete[] index[i];
    }
    
    return 0;
}
