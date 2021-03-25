#ifndef MYAVL
#define MYAVL
#include<iostream>
#include<string>
#define TREENUM 5 
#define INFONUM 10 
using namespace std;

enum Type {NAME,PHONE,QQ,WECHAT,EMAIL,ADDRESS,BIRTHDAY,POSTCODE,SEX,TYPE};
// ��ѯ��ʽ  ǰ5�� 
// ע�� ö������ ����Ϊ tree�����������ǰ�� 

struct Node{
	string information[INFONUM];
	int balance;  // ȡֵ -2 -1 0 1 2 ( �������߶� - �������߶�)  
	Node* left[TREENUM];
	Node* right[TREENUM];
	Node* parent[TREENUM];
	// ���캯����Ҫ�����е�ָ����ΪNULL 
	Node(){
		for(int i=0;i<INFONUM;i++) information[i]="undefined";
		for(int i=0;i<TREENUM;i++){ 
			left[i] = NULL;
			right[i] = NULL;
			parent[i] = NULL;
		} 
		balance = 0;
	}
	Node(string in[INFONUM]){
		for(int i=0;i<INFONUM;i++) information[i] = in[i];
		for(int i=0;i<TREENUM;i++){ 
			left[i] = NULL;
			right[i] = NULL;
			parent[i] = NULL;
		} 
		balance = 0;
	}
}; 

extern Node* Root[TREENUM];
bool Insert(string info[INFONUM]); // �����ȫnode��������Ϣ 
bool Remove(Node*node); // ʹ��һ����Ϣ��ѯ��ɾ��ȫ�� 

// �������� 
Node* search(string info,Type tp);
//����
void insert(Node* node,Type tp);  
//ɾ��
void remove(Node*node,Type tp);
// ǰ�����
void preorder(Node* node,Type tp); 

//��ת 
Node* turnRight(Node* node,Type tp);
Node* turnLeft(Node* node,Type tp);
Node* turnRightLeft(Node* node,Type tp);
Node* turnLeftRight(Node* node,Type tp);
//�ڵ�߶� 
int height(Node* node,Type tp);
// ʹ���ָ�ƽ�� 
void setBalance(Node* node,Type tp);
void rebalance(Node* node,Type tp); 

//////////////////////////////////////////////////

// ����ֵ��ʾ�Ƿ����ɹ�������Ϣ�Ѿ�����ʱ��������� 
bool Insert(string info[INFONUM]){
	bool isExist = false;
	for(int i=0;i<TREENUM;i++){
		if(search(info[i],Type(i))!=NULL){
			isExist = true;
			break;
		}
	} 
	if(isExist) return false; // ��Ϣ�Ѿ����ڣ����������
	Node* tmp = new Node(info);
	for(int i=0;i<TREENUM;i++) 
		insert(tmp,Type(i)); 
	return true;
} 

// ����ֵ��ʾ�Ƿ��Ƴ��ɹ���tree���Ƿ��������Ϣ) 
bool Remove(Node*node){
	if(node==NULL) return false;
	for(int i=0;i<TREENUM;i++) remove(node,Type(i));
	delete node;
	return true;
}

Node* search(string info,Type tp){ 
	Node* node = Root[tp];
	while(node && node->information[tp]!=info){
		if(node->information[tp]<info){
			node = node->right[tp];
		}else{
			node = node->left[tp];
		}
	}
	return node;
} 

// ���ڲ�������ռ�,ͳһ��������
// ��� searchʹ�ã�����ȷ�����л�û����Щ��Ϣ 
// �ܹ��������������˵��tree���治������Щ��Ϣ 
void insert(Node* node,Type tp){
	if(Root[tp]==NULL){
		Root[tp] = node;
		return ; 
	}else{
		Node*tmp = Root[tp];
		while(1){
			if(tmp->information[tp]>node->information[tp]){
				if(tmp->left[tp]!=NULL) tmp=tmp->left[tp];
				else{
					tmp->left[tp] = node;
					node->parent[tp] = tmp;
					rebalance(tmp,tp); 
					return;
				}
			}else{  
				if(tmp->right[tp]!=NULL) tmp=tmp->right[tp];
				else{
					tmp->right[tp] = node;
					node->parent[tp] = tmp;
					rebalance(tmp,tp);
					return;
				}			
			}
		}
	} 
}

// Ҫ�� node�������tree�� 
void remove(Node*node,Type tp){
	if(node->left[tp] and node->right[tp]){
		// ѡ���ұ���Сֵ
		 Node*tmp =  node->right[tp]; // tmp���滻nodeλ�õĽ�� 
		 bool flag = false; // �ж��滻node�Ķ����Ƿ����node��������
		 while(tmp->left[tp]!=NULL){
		 	tmp = tmp->left[tp];
		 	flag = true;
		 }
		 if(flag){
		 	// ��ʱtmp����node�����ӽڵ� 
		 	tmp->parent[tp]->left[tp] = NULL; 
		 	tmp->parent[tp] = node->parent[tp];
			tmp->left[tp] = node->left[tp];
			tmp->right[tp] = node->right[tp];
			//���ø��ڵ���ӽڵ�ָ�� 
			if(tmp->parent[tp]->left[tp]==node) tmp->parent[tp]->left[tp] = tmp;
			else tmp->parent[tp]->right[tp] = tmp;
			//�����ӽڵ�ĸ��ڵ�ָ�� 
		 	if(node->left[tp]) node->left[tp]->parent[tp] = tmp;
		 	if(node->right[tp]) node->right[tp]->parent[tp] = tmp;
		 	
		 }else{
		 	// ��ʱtmp��node�����ӽڵ� 
		 	tmp->parent[tp]->right[tp] = NULL;
		 	//�������ӽڵ��ϵ 
		 	tmp->left[tp] = node->left[tp];
		 	if(node->left[tp]) node->left[tp]->parent[tp] = tmp;
		 	//���ø��ڵ��ϵ 
		 	tmp->parent[tp] = node->parent[tp];
		 	if(node->parent[tp]){
		 		if(node->parent[tp]->left[tp]==node) node->parent[tp]->left[tp] = tmp;
		 		else node->parent[tp]->right[tp] = tmp;
		 	}
		 }
		 rebalance(tmp,tp);
		 if(Root[tp]==node) Root[tp] = tmp;
	}else if(node->left[tp] and !node->right[tp]){
		//���ø���ָ��ָ�� 
		node->left[tp]->parent[tp] = node->parent[tp];
		if(node->parent[tp]!=NULL){
			if(node->parent[tp]->left[tp] == node) node->parent[tp]->left[tp] = node->left[tp];
			else node->parent[tp]->right[tp] = node->left[tp];
		} 
		if(Root[tp]==node) Root[tp] = node->left[tp];
		rebalance(node->left[tp],tp); 
	}else if(!node->left[tp] and node->right[tp]){
		node->right[tp]->parent[tp] = node->parent[tp];
		if(node->parent[tp]!=NULL){
			if(node->parent[tp]->left[tp] == node) node->parent[tp]->left[tp] = node->right[tp];
			else node->parent[tp]->right[tp] = node->right[tp];
		}
		if(Root[tp]==node) Root[tp] = node->right[tp];
		rebalance(node->right[tp],tp); 
	}else{ 
		if(node==Root[tp]){
			Root[tp] = NULL;
		}else{
			if(node->parent[tp]->right[tp] == node) node->parent[tp]->right[tp] = NULL;
			else if(node->parent[tp]->left[tp] == node) node->parent[tp]->left[tp] = NULL;			
			if(node->parent[tp]) rebalance(node->parent[tp],tp); 
		} 
	}
}

void preorder(Node*node,Type tp){
	if(node){
		cout<<node->information[tp]<<" "; 
		if(node->left[tp]) preorder(node->left[tp],tp);
		if(node->right[tp]) preorder(node->right[tp],tp);
	}
}


Node* turnRight(Node* node,Type tp){
	Node* tmp = node->left[tp];
	if(node->parent[tp]!=0){  //  ��node�ĸ��ڵ���ӽڵ���Ϊnode�����ӽڵ� 
        if(node->parent[tp]->right[tp]==node){
            node->parent[tp]->right[tp]=tmp;
        }else{
            node->parent[tp]->left[tp]=tmp;
        }
    }
    tmp->parent[tp]=node->parent[tp];
    node->parent[tp]=tmp;
    node->left[tp]=tmp->right[tp];
    if(node->left[tp]!=0)
        node->left[tp]->parent[tp]=node;
    tmp->right[tp]=node;
    setBalance(node,tp);
    setBalance(tmp,tp);
    return tmp;
} 

Node* turnLeft(Node* node,Type tp){
    Node* tmp=node->right[tp];
    if(node->parent[tp]!=0){
        if(node->parent[tp]->right[tp]==node){
            node->parent[tp]->right[tp]=tmp;
        }else{
            node->parent[tp]->left[tp]=tmp;
        }
    }
    tmp->parent[tp]=node->parent[tp];
    node->parent[tp]=tmp;
    node->right[tp]=tmp->left[tp];
    tmp->left[tp]=node;
    if(node->right[tp]!=0)
        node->right[tp]->parent[tp]=node;
    setBalance(node,tp);
    setBalance(tmp,tp);
    return tmp;
}

Node* turnRightLeft(Node* node,Type tp){
    node->right[tp] = turnRight(node->right[tp],tp);
    return turnLeft(node,tp);	
}

Node* turnLeftRight(Node* node,Type tp){
	node->left[tp] = turnLeft(node->left[tp],tp);
    return turnRight(node,tp);
}

int height(Node* node,Type tp){
    if(node==0){
        return 0;
    }
    int rightheight=height(node->right[tp],tp);
    int leftheight=height(node->left[tp],tp);
    return rightheight > leftheight ? (rightheight+1) : (leftheight+1);
}
void setBalance(Node* node,Type tp){
    if(node)
        node->balance=height(node->right[tp],tp)-height(node->left[tp],tp);
}

void rebalance(Node* node,Type tp){
    setBalance(node,tp);
    if(node->balance== -2){                   //�������������������2�㣬��Ҫͨ����ת������ƽ��
        if(node->left[tp]->balance <=0){          //������ӽڵ�����������������ߣ������һ��������������ӽڵ�����������������ߣ����Ƚ����������ٽ���������
            node=turnRight(node,tp);
        }else{
            node=turnLeftRight(node,tp);
        }
    }else if(node->balance==2){       //�������������������2�㣬��Ҫͨ����ת������ƽ��
        if(node->right[tp]->balance>=0){       //������ӽڵ�����������������ߣ������һ��������������ӽڵ�����������������ͣ����Ƚ����������ٽ���������
            node=turnLeft(node,tp);
        }else{
            node=turnRightLeft(node,tp);
        }
    }
    if(node->parent[tp]){
        rebalance(node->parent[tp],tp);
    }else{
        Root[tp]=node; // ������Խ�Root[tp]��Ϊȫ�ֱ��� 
    }
}
#endif
