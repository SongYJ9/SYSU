#include <iostream>
#include <cmath>
using namespace std;

/* 
	ѧ�ţ�18340146  
	���ܣ��ж��Ƿ�Ϊ���� 
*/

int main()
{
	cout<<"���������Ĵ�С��"<<endl;
	int i,j,k,sum = 0,sum2 = 0;
	cin>>i;
	cout<<"���������"<<endl;
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
