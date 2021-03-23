#include<iostream>
#include "config.h"
#include "grid.h"
#include "chessboard.h"
#include "game.h"

using namespace std;

int main()
{
    Game G;
    G.startGame(4);
    cout<<"��ѡ����Ϸģʽ��"<<endl;
	cout<<"1.����    2.����"<<endl;
	int option;
	cin>>option;
	while(option!=1 && option!=2){
		cout<<"���벻�Ϸ������������룡"<<endl;
		cin>>option; 
	} 
	system("cls");
	G.show();
	int x, y;
	if(option==1){
		while(1){
			cout<<"����������λ�ã�";
			cin>>x>>y;
			while(1){
				if(G.placePiece(x, y))
					break;
				cout<<"���������λ�ò��Ϸ������������룺";
				cin>>x>>y;
			}
			G.show();
			cout<<"��ǰ����÷֣�"<<endl;
			cout<<"AI  : "<<G.evaluateState(G.curState, 2)<<endl;
			cout<<"USER: "<<G.evaluateState(G.curState, 1)<<endl<<endl<<endl;
			if(G.isStart==false){
				cout<<"��Ӯ�ˣ�"<<endl;
				break;
			}
			G.placePieceAI();
	        G.show();
			cout<<"��ǰ����÷֣�"<<endl;
			cout<<"AI  : "<<G.evaluateState(G.curState, 2)<<endl;
			cout<<"USER: "<<G.evaluateState(G.curState, 1)<<endl<<endl<<endl;	
			if(G.isStart==false){
				cout<<"�����ˣ�"<<endl;
				break;
			}	
		}
	}
	else if(option==2){
		while(1){
			G.placePieceAI();
	        G.show();
	        cout<<"��ǰ����÷֣�"<<endl;
			cout<<"AI  : "<<G.evaluateState(G.curState, 1)<<endl;
			cout<<"USER: "<<G.evaluateState(G.curState, 2)<<endl<<endl<<endl;
	        if(G.isStart==false){
				cout<<"�����ˣ�"<<endl;
				break;
			}
			cout<<"����������λ�ã�"; 
			cin>>x>>y;
			while(1){
				if(G.placePiece(x, y))
					break;
				cout<<"���������λ�ò��Ϸ������������룺";
				cin>>x>>y;
			}
			G.show();
	        cout<<"��ǰ����÷֣�"<<endl;
			cout<<"AI  : "<<G.evaluateState(G.curState, 1)<<endl;
			cout<<"USER: "<<G.evaluateState(G.curState, 2)<<endl<<endl<<endl;
			if(G.isStart==false){
				cout<<"��Ӯ�ˣ�"<<endl;
				break;
			}			
		}	
	}
	getchar(); 
}
