#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int sizex = 32, sizey = 32;

struct Matrix{
	int x, y;
	int** v;
}; 

void init(Matrix* m) {
	for (int i = 0; i < m->x; i++)
		for (int j = 0; j < m->y; j++)
			m->v[i][j] = rand() % 10;
}

void print(Matrix* m) {
	for (int i = 0; i < m->x; i++) {
		for (int j = 0; j < m->y; j++) printf("%d ", m->v[i][j]);
		printf("\n");
	}
}

__global__ void add(Matrix* a, Matrix* b, Matrix* c) {
	int x = blockIdx.y * blockDim.y + threadIdx.y, y = blockIdx.x * blockDim.x + threadIdx.x;
	if (x < c->x && y < c->y)
		c->v[x][y] = a->v[x][y] + b->v[x][y];
}

int main(int argc, char* argv[]) {
	int m = strtol(argv[1], NULL, 10), n = strtol(argv[2], NULL, 10);
	timeval t1, t2;
	Matrix *a, *b, *c;
	cudaMallocManaged((void**)&a, sizeof(Matrix));
	cudaMallocManaged((void**)&b, sizeof(Matrix));
	cudaMallocManaged((void**)&c, sizeof(Matrix));
	a->x = m; a->y = n; b->x = m; b->y = n; c->x = m; c->y = n;
	cudaMallocManaged((void**)&a->v, a->x * sizeof(int*));
	cudaMallocManaged((void**)&b->v, b->x * sizeof(int*));
	cudaMallocManaged((void**)&c->v, c->x * sizeof(int*));
    for (int i = 0; i < m; i++) {
        cudaMallocManaged((void**)&a->v[i], a->y * sizeof(int));
        cudaMallocManaged((void**)&b->v[i], b->y * sizeof(int));
        cudaMallocManaged((void**)&c->v[i], c->y * sizeof(int));
    }
	init(a); init(b);
	dim3 block(sizex, sizey), grid(m / sizex, n / sizey);
	
    gettimeofday(&t1, NULL);
	add <<< grid, block >>> (a, b, c);
    cudaDeviceSynchronize();
    gettimeofday(&t2, NULL);
    
    printf("Time: %.4fs\n", (t2.tv_sec-t1.tv_sec+(t2.tv_usec-t1.tv_usec)/1.0e6));
    /*
    printf("Matrix a: \n");
    print(a);
    printf("Matrix b: \n");
    print(b);
    printf("Matrix c: \n");
    print(c);
    */
    return 0;
}