#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <omp.h>

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

void add(Matrix* a, Matrix* b, Matrix* c) {
	#pragma omp parallel for num_threads(4)
	for (int i = 0; i < a->x; i++)
		for (int j = 0; j < a->y; j++)
			c->v[i][j] = a->v[i][j] + b->v[i][j];
}

int main(int argc, char* argv[]) {
	int m = strtol(argv[1], NULL, 10), n = strtol(argv[2], NULL, 10);
	double time;
	LARGE_INTEGER t1, t2, tc;
    QueryPerformanceFrequency(&tc);
	Matrix *a, *b, *c;
	a = (Matrix*)malloc(sizeof(Matrix));
	b = (Matrix*)malloc(sizeof(Matrix));
	c = (Matrix*)malloc(sizeof(Matrix));
	a->x = m; a->y = n; b->x = m; b->y = n; c->x = m; c->y = n;
	a->v = (int**)malloc(m * sizeof(int*));
	b->v = (int**)malloc(m * sizeof(int*));
	c->v = (int**)malloc(m * sizeof(int*));
	for (int i = 0; i < m; i++) {
		a->v[i] = (int*)malloc(n * sizeof(int));
		b->v[i] = (int*)malloc(n * sizeof(int));
		c->v[i] = (int*)malloc(n * sizeof(int));
	}
	init(a); init(b);
	
    QueryPerformanceCounter(&t1);
	add(a, b, c);
	QueryPerformanceCounter(&t2);
	time = (double)(t2.QuadPart-t1.QuadPart)/(double)tc.QuadPart; 
	
    printf("Time: %.6fs\n", time);
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
