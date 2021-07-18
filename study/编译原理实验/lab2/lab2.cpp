#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <iomanip>
#define ll long long
using namespace std;

struct node { // ���ڵ�ṹ��
    string c;
    node *left, *right;
};

string remove(string s) { // ȥ���ַ���ǰ���������
    return s[0] == '(' and s[s.length()-1] == ')' ? s.substr(1, s.length()-2) : s;
}

vector<int> judge(string s) { // �жϲ������������
    vector<int> v;
    for (int i=0; i<s.length(); i++) {
        if ((s[i] >= '0' and s[i] <= '9') or (s[i] == '.') or // ���֡�С���㡢�����Ŷ����ڲ�����
            ((s[i] == '+' or s[i] == '-') and (i == 0 or s[i-1] == '('))) { // �����ŵı�ʶ��+-��ͷ����ǰ����������
            v.push_back(0); // ������
        }
        else v.push_back(1); // �����
    }
    return v;
}

int getIndex(string s, vector<int> v) { // �����ַ������ȼ���͵������
    int j = 0; // �����Ƿ���������
    for (int i=s.length()-1; i>=0; i--) { // �Ӻ���ǰ
        if (s[i] == ')') j++;
        else if (s[i] == '(') j--;
        else if ((s[i] == '-' or s[i] == '+') and v[i] == 1 and j == 0) return i; // ���ҼӼ���
    }
    for (int i=s.length()-1; i>=0; i--) {
        if (s[i] == ')') j++;
        else if (s[i] == '(') j--;
        else if (v[i] == 1 and j == 0) return i; // ���û�мӼ��ţ����ұߵĳ˳��ž������ȼ���͵ķ���
    }
    return -1; // �����������
}

void buildTree(string s, node* root) { // ����
    int index = getIndex(s, judge(s)); // �����ȼ���͵�������������ڵ����
    if (index != -1) { // �ҵõ������������֧�ڵ�
        root->c = s[index];
        root->left = new node();
        root->right = new node();
        buildTree(remove(s.substr(0, index)), root->left); // �ݹ齨��
        buildTree(remove(s.substr(index+1)), root->right);
    }
    else { // �Ҳ������������Ҷ�ڵ�
        root->c = (s[0] == '+' ? s.substr(1) : s); // ȥ������
        root->left = root->right = NULL;
    }
}

void printTreeByLevel(node* root) { // ��α���
    queue<node*> q; // �ڵ����
    queue<int> h; // �߶ȶ���
    q.push(root);
    h.push(0);
    while (q.size()) {
        if (q.front() != NULL) {
            cout << setw(2) << left << q.front()->c << " ";
            q.push(q.front()->left); // �ǿսڵ�Ҳ�������
            q.push(q.front()->right);
            h.push(h.front()+1); // �߶�
            h.push(h.front()+1);
        }
        else cout << setw(2) << left << "x" << " "; // �սڵ����x
        int high = h.front();
        q.pop(); h.pop();
        if (h.size() and h.front() == high+1) cout << endl; // ������һ�㣬����س�
    }
    cout << endl;
}

void printTreeByPos(node* root) { // �������к��������������֤������ȷ��
    if (root != NULL) { // ���ʽ���ĺ���������ں�׺���ʽ
        printTreeByPos(root->left);
        printTreeByPos(root->right);
        cout << root->c << " ";
    }
}

int main() {
    string s;
    cout << "Input: " << endl;
    cin >> s;
    while (s != "q") { // ����"q"����
        node* root = new node();
        buildTree(s, root);
        cout << "Print Tree By Level:" << endl;
        printTreeByLevel(root); // ��α���
        cout << "Print Tree By Pos:" << endl;
        printTreeByPos(root); // ����������͵�һ��ʵ��ĺ�׺���ʽ��֤��ȷ��
        cout << endl;
    	cout << "Input: " << endl;
        cin >> s;
    }
}

/* test:
 3+(4+5/(2-1))
 21+42-30/(5+5)*(4-2)
 2+3*(7-4)+8/4
 ((2+3)*4-(8+2))/5
 1314+25.5*12
 -2*(+3)
 123
 */

