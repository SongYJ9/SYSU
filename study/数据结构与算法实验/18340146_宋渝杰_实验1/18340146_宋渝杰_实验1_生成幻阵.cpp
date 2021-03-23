#include <iostream>
#include <cmath>
using namespace std;

/* 
	学号：18340146  
	功能：输出幻阵 
*/

int main()
{
	cout<<"输入矩阵大小："<<endl;
	int t,i,j,k,l,m;
	cin>>t;
	int a[t][t];
	for(i=0;i<t;i++){
		for(j=0;j<t;j++){
			a[i][j] = 0;
		}
	}
	if(t%2 == 1){
		j=0;
		k=t/2;
		for(i=1;i<=t*t;i++){
			l=j;m=k;
			a[j][k] = i;
			l--;
			if(l == -1) l = t-1;
			m++;
			if(m == t) m = 0;
			if(a[l][m] == 0){
				j--;
				if(j == -1) j = t-1;
				k++;
				if(k == t) k = 0;
			}
			else{
				j++;
				if(j == t) j = 0; 
			}
		}
		for(i=0;i<t;i++){
			for(j=0;j<t;j++){
				cout<<a[i][j]<<" ";
			}
			cout<<endl;
		}
	}
	else{
		
	}
}

