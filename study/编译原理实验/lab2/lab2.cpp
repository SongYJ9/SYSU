#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <iomanip>
#define ll long long
using namespace std;

struct node { // 树节点结构体
    string c;
    node *left, *right;
};

string remove(string s) { // 去除字符串前后多余括号
    return s[0] == '(' and s[s.length()-1] == ')' ? s.substr(1, s.length()-2) : s;
}

vector<int> judge(string s) { // 判断操作数和运算符
    vector<int> v;
    for (int i=0; i<s.length(); i++) {
        if ((s[i] >= '0' and s[i] <= '9') or (s[i] == '.') or // 数字、小数点、正负号都属于操作数
            ((s[i] == '+' or s[i] == '-') and (i == 0 or s[i-1] == '('))) { // 正负号的标识：+-开头或者前面是左括号
            v.push_back(0); // 操作数
        }
        else v.push_back(1); // 运算符
    }
    return v;
}

int getIndex(string s, vector<int> v) { // 计算字符串优先级最低的运算符
    int j = 0; // 标明是否在括号内
    for (int i=s.length()-1; i>=0; i--) { // 从后往前
        if (s[i] == ')') j++;
        else if (s[i] == '(') j--;
        else if ((s[i] == '-' or s[i] == '+') and v[i] == 1 and j == 0) return i; // 先找加减号
    }
    for (int i=s.length()-1; i>=0; i--) {
        if (s[i] == ')') j++;
        else if (s[i] == '(') j--;
        else if (v[i] == 1 and j == 0) return i; // 如果没有加减号，最右边的乘除号就是优先级最低的符号
    }
    return -1; // 不存在运算符
}

void buildTree(string s, node* root) { // 建树
    int index = getIndex(s, judge(s)); // 找优先级最低的运算符，即根节点符号
    if (index != -1) { // 找得到运算符，即分支节点
        root->c = s[index];
        root->left = new node();
        root->right = new node();
        buildTree(remove(s.substr(0, index)), root->left); // 递归建树
        buildTree(remove(s.substr(index+1)), root->right);
    }
    else { // 找不到运算符，即叶节点
        root->c = (s[0] == '+' ? s.substr(1) : s); // 去掉正号
        root->left = root->right = NULL;
    }
}

void printTreeByLevel(node* root) { // 层次遍历
    queue<node*> q; // 节点队列
    queue<int> h; // 高度队列
    q.push(root);
    h.push(0);
    while (q.size()) {
        if (q.front() != NULL) {
            cout << setw(2) << left << q.front()->c << " ";
            q.push(q.front()->left); // 是空节点也放入队列
            q.push(q.front()->right);
            h.push(h.front()+1); // 高度
            h.push(h.front()+1);
        }
        else cout << setw(2) << left << "x" << " "; // 空节点输出x
        int high = h.front();
        q.pop(); h.pop();
        if (h.size() and h.front() == high+1) cout << endl; // 遍历完一层，输出回车
    }
    cout << endl;
}

void printTreeByPos(node* root) { // 对树进行后序遍历，用于验证树的正确性
    if (root != NULL) { // 表达式树的后序遍历等于后缀表达式
        printTreeByPos(root->left);
        printTreeByPos(root->right);
        cout << root->c << " ";
    }
}

int main() {
    string s;
    cout << "Input: " << endl;
    cin >> s;
    while (s != "q") { // 输入"q"结束
        node* root = new node();
        buildTree(s, root);
        cout << "Print Tree By Level:" << endl;
        printTreeByLevel(root); // 层次遍历
        cout << "Print Tree By Pos:" << endl;
        printTreeByPos(root); // 后序遍历，和第一个实验的后缀表达式验证正确性
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

