//���̸���

#ifndef GRID_H
#define GRID_H
#include "config.h"

class Grid :CONFIG {
	public:
	    int type; //����
	    
	    Grid() {
	        type = EMPTY;
	    }
	    
	    Grid(int t) {
	        type = t;
	    }
	    
	    void grid(int t = EMPTY) {
	        type = t;
	    }
	    
	    int isEmpty() {
	        return type == EMPTY ? true : false;
	    }
};
#endif
