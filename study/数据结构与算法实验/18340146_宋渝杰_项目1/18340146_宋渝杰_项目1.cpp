#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <windows.h>
#include <conio.h> 
using namespace std;

vector <int> input()//���뺯�� 
{
	bool flag = true; //���ܱ�־���� 
	vector <int> tmp;
	while (true){
		if(flag){
			cout << "\n---������һ�д����ȵĻ𳵵ı�ţ�" << endl<< endl;
			flag=false;
		} 
		int n;
		cin >> n;
		if(!cin.good()){
			cin.clear();//��ȡʧ��ʱ��ջ����� 
			cin.sync();
			cout << "--�����ʽ����!" << endl;
			cout << "--����������!" << endl;
			Sleep(500);	//������ͣ0.5s 
			flag=true;
			tmp.clear();
			system("cls");
			continue;
		}
		tmp.push_back(n); 
		if (cin.get() == '\n') break;//����س���ʱ�������� 
	}
	return tmp;
}


int main()
{
	
	vector<stack <int> > bufferRoad;//������
	vector<int> outQueue; //�������,��Ҫ���ڽ�����������룬�����벻������1~n 
	stack<int> wait; //�洢���Ļ𳵳�����
	int	step = 0;	//�����ܲ��� 
	int	index = 0;	//��� outqueue ָ����ǰӦ����ĳ����� 
	int	top;	// ��쳵���ͷ����� 
	int	i; 		//ѭ����������		
	
	outQueue=input(); 
	for(i=0;i<outQueue.size();i++){  //ȷ���������ݸ�ʽ�����,��������ջ 
		wait.push(outQueue[i]); 
	}

	sort(outQueue.begin(),outQueue.end());//ָ���𳵳���˳�� 

	cout << endl << "---���̣�" << endl<< endl;
	while (wait.empty() == 0) //���������Ļ𳵳���ʱ 
	{
		top = wait.top();//ȡ���ȴ���ͷ�ڻ𳵳��� 
		
		
		if (top == outQueue[index]) {//�ж��Ƿ���ֱ�ӳ��� 
			cout <<"   "<< outQueue[index] << "�ų���ֱ�ӳ���" << endl;
			wait.pop();
			index++;
			step++;
			continue;
		}
		else {//�������ֱ�ӳ��� 
			for (i = 0; i < bufferRoad.size(); i++) {
				if (bufferRoad[i].empty() == 0 and bufferRoad[i].top() == outQueue[index]) {//�жϻ��������Ƿ��г�����Գ��� 
					cout << "   " << outQueue[index] << "�ų����" << i + 1 << "�Ż���������" << endl;
					bufferRoad[i].pop();
					index++;
					step++;
					goto th;
				}
			}
			//���û�г�����Գ��� 
			for (i = 0; i < bufferRoad.size(); i++) {
				if (bufferRoad[i].empty() == 1 or top <= bufferRoad[i].top()) {//�ж��ܷ�������еĻ����� 
					bufferRoad[i].push(top);
					cout << "   " << top << "�ų������" << i+1 << "�Ż�����" << endl;
					wait.pop();
					step++;
					goto th;
				}
			}
			//������ܷ����κ����еĻ����������½�һ���µĻ����� 
			stack<int> newRoad;
			newRoad.push(top);
			wait.pop();
			step++;
			bufferRoad.push_back(newRoad);
			cout << "   " << top << "�ų������" << bufferRoad.size() << "�Ż�����" << endl;
		}
		th:;//goto�������ֱ�ӿ�ʼ�µ�ѭ�� 
	}
	
	//�����ĳ�����ȫ���������뻺����ʱ����������ʣ�µĳ��᣺ 
	for (i = 0; i < bufferRoad.size(); i++) {
		if (bufferRoad[i].empty() == 0 and bufferRoad[i].top() == outQueue[index]) {//�ж��ĸ��������ĳ�����Գ��� 
			cout << "   " << outQueue[index] << "�ų����" << i + 1 << "�Ż���������" << endl;
			step++;
			index++;
			bufferRoad[i].pop();
			i = -1;
			continue;
		}
	}
	
	//������̽��� 
	cout << endl<< "---�����ܲ�����" << step << endl;
	cout << "---��Ҫ������������" << bufferRoad.size() << endl;
	cin.sync();
	cin.clear();
	cout<<"\n--��������˳�...";
	getch();
}
