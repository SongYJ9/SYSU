#include <iostream>
#include <cmath>
using namespace std;

/* 
	学号：18340146  
	功能：找出8位数以内的雷劈数
*/
 
void thunder()//求雷劈数 
{
	for(int i = 3163;i < 10000; i++){
		// 求出数字的位数,命名为c 
		int a = i*i,c=0;
		while(a){
			a/=10;
			c++;
		}
		// 判断是否为雷劈数 
		int left,right;
		for(int j = 1;j < c; j++){
			left = i*i;
			right = left%(int)pow(10,j);
			left = left/(int)pow(10,j);
			if(left + right == i)
			{
				cout<<i*i<<endl;//输出雷劈数 
			}
		}
	}
}

int main()
{
	cout<<"8位数中的雷劈数："<<endl;
	thunder();
}
