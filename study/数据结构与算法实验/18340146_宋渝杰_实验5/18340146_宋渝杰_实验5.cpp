#include <bits/stdc++.h>

using namespace std;

struct Node //�ڵ�����
{
	int value; //ֵ
	Node* left; //��ڵ�
	Node* right; //�ҽڵ�
};

class Tree //������
{
	Node* root; //���ڵ�
public:
	Tree() {
		root = NULL;
	}
	Tree(int v) { //���ø��ڵ�Ĺ��캯��
		root = new Node();
		root->value = v;
		root->left = root->right = NULL;
	}
	void push(Node* root, vector<Node*>& vec) { //�������ղ�η���vector��
		if (root != NULL) {
			vec.push_back(root);
			push(root->left, vec);
			push(root->right, vec);
		}
	}
	Node* find(Node* root, int fv) { //Ѱ��ֵΪfv�ĸ��ڵ�
		vector<Node*> vec;
		push(root, vec);
		int i;
		for (i = 0; i < vec.size(); i++) {
			if (vec[i]->value == fv) return vec[i];
		}
		if (i == vec.size()) return NULL;
	}
	void Insert(int fv, int v, int place) { //����������½�ֵΪv���ӽڵ���뵽ֵΪfv�ĸ��ڵ㣬place=1ʱΪ��ڵ㣬2Ϊ�ҽڵ�
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
	void pre(Node* root) { //�������
		if (root != NULL) {
			cout << root->value << " ";
			pre(root->left);
			pre(root->right);
		}
	}
	void ino(Node* root) { //�������
		if (root != NULL) {
			ino(root->left);
			cout << root->value << " ";
			ino(root->right);
		}
	}
	void pos(Node* root) { //�������
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
	void interChange() { //�������е����ҽڵ�
		change(root);
		/* �ǵݹ�汾
		vector<Node*> vec;
		push(root, vec);
		Node* temp;
		for (int i = 0; i < vec.size(); i++) {
			temp = vec[i]->left;
			vec[i]->left = vec[i]->right;
			vec[i]->right = temp;
		} */
	}
	void show() { //���ַ�ʽչʾ��
		cout << "�������: ";
		pre(root);
		cout << endl << "�������: ";
		ino(root);
		cout << endl << "�������: ";
		pos(root);
		cout << endl << "���ڵ�������ӽڵ�: "<<endl;
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
	cout << "Hello! �������Ѿ����ã�����һ��data(���)Ϊ1��root" << endl;
	cout << "��������Ĳ�������ܴ�����" << endl;
	Tree tree(1); //�½�����һ��root��ֵΪ1����
	int i, n, x, y, z;
	cin >> n;
	cout << "��������Ĳ�����������������������ֱ�����ڵ��data��������ӽڵ��data�������λ�ã�1Ϊ���ӽڵ㣬2Ϊ���ӽڵ㣩��" << endl;
	for (i = 0; i < n; i++) {
		cin >> x >> y >> z;
		tree.Insert(x, y, z);
	}
	cout << endl << "����֮ǰ��" << endl;
	tree.show();
	tree.interChange();
	cout << "����֮��" << endl;
	tree.show();
}
