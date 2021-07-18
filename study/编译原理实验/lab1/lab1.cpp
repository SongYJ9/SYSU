#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#define ll long long
using namespace std;

void tran(string s) { // ��׺ת��׺
    vector<int> a; // һ���ж��ǲ���������������ĸ������飨0����������1���������2����һ����������
    int j = 0;
    for (int i=0; i<s.length(); i++) {
        if ((s[i] >= '0' and s[i] <= '9') or (s[i] == '.') or // ���֡�С���㡢�����Ŷ����ڲ�����
            ((s[i] == '+' or s[i] == '-') and (i == 0 or s[i-1] == '('))) { // �����ŵı�ʶ��+-��ͷ����ǰ����������
            if (j == 0) { // ����ǵ�һ��������
                a.push_back(2);
                j = 1;
            }
            else a.push_back(0); // ��ͨ������
        }
        else a.push_back(1); // �����
    }
    stack<char> t;
    for (int i=0; i<s.length(); i++) {
        if (s[i] == '(') t.push(s[i]); // �����ţ�ֱ�ӽ�ջ
        else if (s[i] == ')') { // �����ţ�һֱ��ջ�������ֱ��������������ֹ
            while (t.top() != '(') {
                cout << " " << t.top();
                t.pop();
            }
            t.pop(); // �����ų�ջ�������
        }
        else if (s[i] == '*' or s[i] == '/') { // �˳�����
            while (t.size() and (t.top() == '*' or t.top() == '/')) { // ջ����*/���ջ�����
                cout << " " << t.top();
                t.pop();
            }
            t.push(s[i]); // �˳����Ž�ջ
        }
        else if ((s[i] == '+' or s[i] == '-') and a[i] == 1) { // �Ӽ����ţ�ע�ⲻ�������ţ�
            while (t.size() and t.top() != '(') { // һֱ��ջ�������ֱ��������������ֹ
                cout << " " << t.top();
                t.pop();
            }
            t.push(s[i]); // �Ӽ����Ž�ջ
        }
        else { // �����������������ţ�
            if (s[i] == '+') { // ���Ų����
                if (a[i] == 0) cout << " ";
            }
            else if (a[i] == 2 or i == 0 or a[i-1] != 1) cout << s[i]; // ��һ������������ǰ��һ������Ҳ�ǲ�������������ո�
            else cout << " " << s[i]; // �������������������������������������
        }
    }
    while (t.size()) { // ջ��ʣ���������ջ�����
        cout << " " << t.top();
        t.pop();
    }
    cout << endl;
}

int main() {
    string s;
    cout << "Input: " << endl;
    cin >> s;
    while (s != "q") { // ����"q"����
    	cout << "Output: " << endl;
        tran(s);
    	cout << "Input: " << endl;
        cin >> s;
    }
}

