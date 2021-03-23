#include <iostream>
#include <cmath>
using namespace std;

/* 
	学号：18340146  
	功能：判断是否为幻阵 
*/

int main()
{
	cout<<"请输入矩阵的大小："<<endl;
	int i,j,k,sum = 0,sum2 = 0;
	cin>>i;
	cout<<"请输入矩阵："<<endl;
	int a[i][i];
	for(j=0;j<i;j++){
		for(k=0;k<i;k++){
			cin>>a[j][k];
		}
	}
	for(j=0;j<i;j++){
		sum += a[0][j];
	}
	for(j=1;j<i;j++){
		for(k=0;k<i;k++){
			sum2 += a[j][k];
		}
		if(sum2 != sum){
			cout<<"No!"<<endl;
			return 0;
		}
		sum2 = 0;
	}
	for(j=0;j<i;j++){
		for(k=0;k<i;k++){
			sum2 += a[k][j];
		}
		if(sum2 != sum){
			cout<<"No!"<<endl;
			return 0;
		}
		sum2 = 0;
	}
	for(j=0;j<i;j++){
		sum2 += a[j][j];
	}
	if(sum2 != sum){
		cout<<"No!"<<endl;
		return 0;
	}
	sum2 = 0;
	for(j=0;j<i;j++){
		sum2 += a[i-j-1][j];
	}
	if(sum2 != sum){
		cout<<"No!"<<endl;
		return 0;
	}
	sum2 = 0;
	cout<<"Yes!"<<endl;
}
