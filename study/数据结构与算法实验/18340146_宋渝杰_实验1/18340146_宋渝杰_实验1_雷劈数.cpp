#include <iostream>
#include <cmath>
using namespace std;

/* 
	ѧ�ţ�18340146  
	���ܣ��ҳ�8λ�����ڵ�������
*/
 
void thunder()//�������� 
{
	for(int i = 3163;i < 10000; i++){
		// ������ֵ�λ��,����Ϊc 
		int a = i*i,c=0;
		while(a){
			a/=10;
			c++;
		}
		// �ж��Ƿ�Ϊ������ 
		int left,right;
		for(int j = 1;j < c; j++){
			left = i*i;
			right = left%(int)pow(10,j);
			left = left/(int)pow(10,j);
			if(left + right == i)
			{
				cout<<i*i<<endl;//��������� 
			}
		}
	}
}

int main()
{
	cout<<"8λ���е���������"<<endl;
	thunder();
}
