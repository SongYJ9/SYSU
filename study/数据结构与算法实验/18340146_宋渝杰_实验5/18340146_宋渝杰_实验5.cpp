#include <bits/stdc++.h>

using namespace std;

struct Node //节点性质
{
	int value; //值
	Node* left; //左节点
	Node* right; //右节点
};

class Tree //二叉树
{
	Node* root; //根节点
public:
	Tree() {
		root = NULL;
	}
	Tree(int v) { //设置根节点的构造函数
		root = new Node();
		root->value = v;
		root->left = root->right = NULL;
	}
	void push(Node* root, vector<Node*>& vec) { //将树按照层次放入vector中
		if (root != NULL) {
			vec.push_back(root);
			push(root->left, vec);
			push(root->right, vec);
		}
	}
	Node* find(Node* root, int fv) { //寻找值为fv的父节点
		vector<Node*> vec;
		push(root, vec);
		int i;
		for (i = 0; i < vec.size(); i++) {
			if (vec[i]->value == fv) return vec[i];
		}
		if (i == vec.size()) return NULL;
	}
	void Insert(int fv, int v, int place) { //插入操作，新建值为v的子节点插入到值为fv的父节点，place=1时为左节点，2为右节点
		Node* n = find(root, fv);
		Node* n2 = new Node();
		n2->left = n2->right = NULL;
		n2->value = v;
		if (n != NULL) {
			if (place == 1 and n->left == NULL) {
				n->left = n2;
			}
			else if (place == 2 and n->right == NULL) {
				n->right = n2;
			}
			else delete n2;
		}
		else delete n2;
	}
	void pre(Node* root) { //先序遍历
		if (root != NULL) {
			cout << root->value << " ";
			pre(root->left);
			pre(root->right);
		}
	}
	void ino(Node* root) { //中序遍历
		if (root != NULL) {
			ino(root->left);
			cout << root->value << " ";
			ino(root->right);
		}
	}
	void pos(Node* root) { //后序遍历
		if (root != NULL) {
			pos(root->left);
			pos(root->right);
			cout << root->value << " ";
		}
	}
	void change(Node* root) {
		if (root) {
			swap(root->left, root->right);
			change(root->left);
			change(root->right);
		}
	} 
	void interChange() { //交换所有的左右节点
		change(root);
		/* 非递归版本
		vector<Node*> vec;
		push(root, vec);
		Node* temp;
		for (int i = 0; i < vec.size(); i++) {
			temp = vec[i]->left;
			vec[i]->left = vec[i]->right;
			vec[i]->right = temp;
		} */
	}
	void show() { //多种方式展示树
		cout << "先序遍历: ";
		pre(root);
		cout << endl << "中序遍历: ";
		ino(root);
		cout << endl << "后序遍历: ";
		pos(root);
		cout << endl << "父节点和左右子节点: "<<endl;
		vector<Node*> vec;
		push(root, vec);
		for (int i = 0; i < vec.size(); i++) {
			cout << vec[i]->value << " ";
			if (vec[i]->left != NULL) cout << vec[i]->left->value << " ";
			else cout << "NULL ";
			if (vec[i]->right != NULL) cout << vec[i]->right->value << " ";
			else cout << "NULL ";
			cout << endl;
		}
		cout << endl;
	}
};

int main()
{
	cout << "Hello! 您的树已经建好，具有一个data(编号)为1的root" << endl;
	cout << "请输入你的插入操作总次数：" << endl;
	Tree tree(1); //新建好了一个root的值为1的树
	int i, n, x, y, z;
	cin >> n;
	cout << "请输入你的插入操作：（输入三个数，分别代表父节点的data，插入的子节点的data，插入的位置（1为左子节点，2为右子节点））" << endl;
	for (i = 0; i < n; i++) {
		cin >> x >> y >> z;
		tree.Insert(x, y, z);
	}
	cout << endl << "交换之前：" << endl;
	tree.show();
	tree.interChange();
	cout << "交换之后：" << endl;
	tree.show();
}
