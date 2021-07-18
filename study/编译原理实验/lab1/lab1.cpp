#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#define ll long long
using namespace std;

void tran(string s) { // 中缀转后缀
    vector<int> a; // 一个判断是操作数还是运算符的辅助数组（0：操作数；1：运算符；2：第一个操作数）
    int j = 0;
    for (int i=0; i<s.length(); i++) {
        if ((s[i] >= '0' and s[i] <= '9') or (s[i] == '.') or // 数字、小数点、正负号都属于操作数
            ((s[i] == '+' or s[i] == '-') and (i == 0 or s[i-1] == '('))) { // 正负号的标识：+-开头或者前面是左括号
            if (j == 0) { // 如果是第一个操作数
                a.push_back(2);
                j = 1;
            }
            else a.push_back(0); // 普通操作数
        }
        else a.push_back(1); // 运算符
    }
    stack<char> t;
    for (int i=0; i<s.length(); i++) {
        if (s[i] == '(') t.push(s[i]); // 左括号：直接进栈
        else if (s[i] == ')') { // 右括号：一直出栈并输出，直到遇到左括号中止
            while (t.top() != '(') {
                cout << " " << t.top();
                t.pop();
            }
            t.pop(); // 左括号出栈但不输出
        }
        else if (s[i] == '*' or s[i] == '/') { // 乘除符号
            while (t.size() and (t.top() == '*' or t.top() == '/')) { // 栈顶是*/则出栈并输出
                cout << " " << t.top();
                t.pop();
            }
            t.push(s[i]); // 乘除符号进栈
        }
        else if ((s[i] == '+' or s[i] == '-') and a[i] == 1) { // 加减符号（注意不是正负号）
            while (t.size() and t.top() != '(') { // 一直出栈并输出，直到遇到左括号中止
                cout << " " << t.top();
                t.pop();
            }
            t.push(s[i]); // 加减符号进栈
        }
        else { // 操作数（包括正负号）
            if (s[i] == '+') { // 正号不输出
                if (a[i] == 0) cout << " ";
            }
            else if (a[i] == 2 or i == 0 or a[i-1] != 1) cout << s[i]; // 第一个操作数或者前面一个符号也是操作数，则无需空格
            else cout << " " << s[i]; // 其余情况：操作数与操作数、操作数与运算符
        }
    }
    while (t.size()) { // 栈中剩余运算符出栈并输出
        cout << " " << t.top();
        t.pop();
    }
    cout << endl;
}

int main() {
    string s;
    cout << "Input: " << endl;
    cin >> s;
    while (s != "q") { // 输入"q"结束
    	cout << "Output: " << endl;
        tran(s);
    	cout << "Input: " << endl;
        cin >> s;
    }
}

