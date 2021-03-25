#ifndef MYAVL
#define MYAVL
#include<iostream>
#include<string>
#define TREENUM 5 
#define INFONUM 10 
using namespace std;

enum Type {NAME,PHONE,QQ,WECHAT,EMAIL,ADDRESS,BIRTHDAY,POSTCODE,SEX,TYPE};
// 查询方式  前5个 
// 注意 枚举类型 中作为 tree索引的项放在前面 

struct Node{
	string information[INFONUM];
	int balance;  // 取值 -2 -1 0 1 2 ( 左子树高度 - 右子树高度)  
	Node* left[TREENUM];
	Node* right[TREENUM];
	Node* parent[TREENUM];
	// 构造函数需要把所有的指针置为NULL 
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
bool Insert(string info[INFONUM]); // 必须给全node的所有信息 
bool Remove(Node*node); // 使用一种信息查询、删除全部 

// 查找内容 
Node* search(string info,Type tp);
//插入
void insert(Node* node,Type tp);  
//删除
void remove(Node*node,Type tp);
// 前序遍历
void preorder(Node* node,Type tp); 

//旋转 
Node* turnRight(Node* node,Type tp);
Node* turnLeft(Node* node,Type tp);
Node* turnRightLeft(Node* node,Type tp);
Node* turnLeftRight(Node* node,Type tp);
//节点高度 
int height(Node* node,Type tp);
// 使树恢复平衡 
void setBalance(Node* node,Type tp);
void rebalance(Node* node,Type tp); 

//////////////////////////////////////////////////

// 返回值表示是否插入成功，当信息已经存在时不允许插入 
bool Insert(string info[INFONUM]){
	bool isExist = false;
	for(int i=0;i<TREENUM;i++){
		if(search(info[i],Type(i))!=NULL){
			isExist = true;
			break;
		}
	} 
	if(isExist) return false; // 信息已经存在，不允许添加
	Node* tmp = new Node(info);
	for(int i=0;i<TREENUM;i++) 
		insert(tmp,Type(i)); 
	return true;
} 

// 返回值表示是否移除成功（tree中是否有这个信息) 
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

// 在内部不申请空间,统一管理申请
// 配合 search使用，必须确保树中还没有这些信息 
// 能够进入这个函数就说明tree里面不存在这些信息 
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

// 要求 node必须存在tree中 
void remove(Node*node,Type tp){
	if(node->left[tp] and node->right[tp]){
		// 选择右边最小值
		 Node*tmp =  node->right[tp]; // tmp是替换node位置的结点 
		 bool flag = false; // 判断替换node的对象是否就是node的右子树
		 while(tmp->left[tp]!=NULL){
		 	tmp = tmp->left[tp];
		 	flag = true;
		 }
		 if(flag){
		 	// 此时tmp不是node的右子节点 
		 	tmp->parent[tp]->left[tp] = NULL; 
		 	tmp->parent[tp] = node->parent[tp];
			tmp->left[tp] = node->left[tp];
			tmp->right[tp] = node->right[tp];
			//设置父节点的子节点指向 
			if(tmp->parent[tp]->left[tp]==node) tmp->parent[tp]->left[tp] = tmp;
			else tmp->parent[tp]->right[tp] = tmp;
			//设置子节点的父节点指向 
		 	if(node->left[tp]) node->left[tp]->parent[tp] = tmp;
		 	if(node->right[tp]) node->right[tp]->parent[tp] = tmp;
		 	
		 }else{
		 	// 此时tmp是node的右子节点 
		 	tmp->parent[tp]->right[tp] = NULL;
		 	//设置左子节点关系 
		 	tmp->left[tp] = node->left[tp];
		 	if(node->left[tp]) node->left[tp]->parent[tp] = tmp;
		 	//设置父节点关系 
		 	tmp->parent[tp] = node->parent[tp];
		 	if(node->parent[tp]){
		 		if(node->parent[tp]->left[tp]==node) node->parent[tp]->left[tp] = tmp;
		 		else node->parent[tp]->right[tp] = tmp;
		 	}
		 }
		 rebalance(tmp,tp);
		 if(Root[tp]==node) Root[tp] = tmp;
	}else if(node->left[tp] and !node->right[tp]){
		//设置父子指针指向 
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
	if(node->parent[tp]!=0){  //  将node的父节点的子节点置为node的左子节点 
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
    if(node->balance== -2){                   //如果左子树比右子树高2层，需要通过旋转来重新平衡
        if(node->left[tp]->balance <=0){          //如果左子节点的左子树比右子树高，则进行一次右旋；如果左子节点的右子树比左子树高，则先进行左旋，再进行右旋。
            node=turnRight(node,tp);
        }else{
            node=turnLeftRight(node,tp);
        }
    }else if(node->balance==2){       //如果右子树比左子树高2层，需要通过旋转来重新平衡
        if(node->right[tp]->balance>=0){       //如果右子节点的右子树比左子树高，则进行一次左旋；如果右子节点的右子树比左子树低，则先进行右旋，再进行左旋。
            node=turnLeft(node,tp);
        }else{
            node=turnRightLeft(node,tp);
        }
    }
    if(node->parent[tp]){
        rebalance(node->parent[tp],tp);
    }else{
        Root[tp]=node; // 后面可以将Root[tp]设为全局变量 
    }
}
#endif
