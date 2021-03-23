#include <bits/stdc++.h>

using namespace std;

bool cmp(int a, int b) {
	return a > b;
}

void check(vector<int> arr, vector<vector<int> >& darr, stack<int>& sta, stack<int>& sindex, int index, int num, int t) {
	int i, j, temp;
	for (i = index; i < arr.size(); i++) {
		sta.push(arr[i]);
		sindex.push(i);
		num += arr[i];
		if (num > t) {
			num -= sta.top();
			sta.pop();
			sindex.pop();
		}
		else if (num == t) {
			stack<int> sta2(sta);
			vector<int> a;
			while (!sta2.empty()) {
				a.push_back(sta2.top());
				sta2.pop();
			}
			darr.push_back(a);
			if (i != arr.size() - 1) {
				sta.pop();
				sindex.pop();
				num -= arr[i];
			}
		}
		if (i == arr.size() - 1) {
			if (sta.size() > 1){
				num -= sta.top();
				sta.pop();
				num -= sta.top();
				sta.pop();
				sindex.pop();
				temp = sindex.top();
				sindex.pop();
				check(arr, darr, sta, sindex, temp + 1, num, t);
			}
		}
	}
}

int main()
{
	vector<int> arr;
	stack<int> sta, sindex;
	vector<vector<int> > darr;
	int i, j, k, n, t, x, num = 0;
	cout << "请输入背包的体积： " << endl;
	cin >> t;
	cout << "请输入物品的个数： " << endl;
	cin >> n;
	cout << "请输入 " << n << " 个物品的体积：" << endl;
	for (i = 0; i < n; i++) {
		cin >> x;
		arr.push_back(x);
	}
	sort(arr.begin(), arr.end(), cmp);
	check(arr, darr, sta, sindex, 0, 0, t);
	cout << "一共有 " << darr.size() << " 组解： " << endl;
	for (i = 0; i < darr.size(); i++) {
		for (j = 0; j < darr[i].size(); j++) {
			cout << darr[i][j] << " ";
		}
		cout << endl;
	}
}
