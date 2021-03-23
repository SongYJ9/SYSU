#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <windows.h>
#include <conio.h> 
using namespace std;

vector <int> input()//输入函数 
{
	bool flag = true; //功能标志参数 
	vector <int> tmp;
	while (true){
		if(flag){
			cout << "\n---请输入一列待调度的火车的编号：" << endl<< endl;
			flag=false;
		} 
		int n;
		cin >> n;
		if(!cin.good()){
			cin.clear();//读取失败时清空缓冲区 
			cin.sync();
			cout << "--输入格式有误!" << endl;
			cout << "--请重新输入!" << endl;
			Sleep(500);	//程序暂停0.5s 
			flag=true;
			tmp.clear();
			system("cls");
			continue;
		}
		tmp.push_back(n); 
		if (cin.get() == '\n') break;//输入回车键时结束输入 
	}
	return tmp;
}


int main()
{
	
	vector<stack <int> > bufferRoad;//缓冲轨道
	vector<int> outQueue; //输出队列,主要用于解决非正常输入，即输入不完整的1~n 
	stack<int> wait; //存储入轨的火车车厢编号
	int	step = 0;	//调度总步数 
	int	index = 0;	//结合 outqueue 指定当前应出轨的车厢编号 
	int	top;	// 入轨车厢的头部编号 
	int	i; 		//循环遍历参数		
	
	outQueue=input(); 
	for(i=0;i<outQueue.size();i++){  //确定输入数据格式无误后,将数据入栈 
		wait.push(outQueue[i]); 
	}

	sort(outQueue.begin(),outQueue.end());//指明火车出轨顺序 

	cout << endl << "---过程：" << endl<< endl;
	while (wait.empty() == 0) //当存在入轨的火车车厢时 
	{
		top = wait.top();//取出等待的头节火车车厢 
		
		
		if (top == outQueue[index]) {//判断是否能直接出轨 
			cout <<"   "<< outQueue[index] << "号车厢直接出轨" << endl;
			wait.pop();
			index++;
			step++;
			continue;
		}
		else {//如果不能直接出轨 
			for (i = 0; i < bufferRoad.size(); i++) {
				if (bufferRoad[i].empty() == 0 and bufferRoad[i].top() == outQueue[index]) {//判断缓冲轨道中是否有车厢可以出轨 
					cout << "   " << outQueue[index] << "号车厢从" << i + 1 << "号缓冲轨道出轨" << endl;
					bufferRoad[i].pop();
					index++;
					step++;
					goto th;
				}
			}
			//如果没有车厢可以出轨 
			for (i = 0; i < bufferRoad.size(); i++) {
				if (bufferRoad[i].empty() == 1 or top <= bufferRoad[i].top()) {//判断能否放入已有的缓冲轨道 
					bufferRoad[i].push(top);
					cout << "   " << top << "号车厢进入" << i+1 << "号缓冲轨道" << endl;
					wait.pop();
					step++;
					goto th;
				}
			}
			//如果不能放入任何已有的缓冲轨道，则新建一个新的缓冲轨道 
			stack<int> newRoad;
			newRoad.push(top);
			wait.pop();
			step++;
			bufferRoad.push_back(newRoad);
			cout << "   " << top << "号车厢进入" << bufferRoad.size() << "号缓冲轨道" << endl;
		}
		th:;//goto语句用于直接开始新的循环 
	}
	
	//当入轨的车厢已全部出轨或进入缓冲轨道时，处理缓冲轨道剩下的车厢： 
	for (i = 0; i < bufferRoad.size(); i++) {
		if (bufferRoad[i].empty() == 0 and bufferRoad[i].top() == outQueue[index]) {//判断哪个缓冲轨道的车厢可以出轨 
			cout << "   " << outQueue[index] << "号车厢从" << i + 1 << "号缓冲轨道出轨" << endl;
			step++;
			index++;
			bufferRoad[i].pop();
			i = -1;
			continue;
		}
	}
	
	//出轨过程结束 
	cout << endl<< "---调度总步数：" << step << endl;
	cout << "---需要缓冲轨道数量：" << bufferRoad.size() << endl;
	cin.sync();
	cin.clear();
	cout<<"\n--按任意键退出...";
	getch();
}
