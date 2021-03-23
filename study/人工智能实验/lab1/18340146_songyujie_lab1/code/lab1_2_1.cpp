#include <bits/stdc++.h>
using namespace std;

struct node{
	int index; // 训练数据index 
	double l; // 测试数据与该训练数据的距离 
};

int cmp(node a,node b) {
	return a.l<b.l; // 距离升序排序 
}

int k = 10,p = 3; // 参数 

unordered_map<int,unordered_map<string,int>> train; // 训练集的词频 

double counting(int i,unordered_map<string,int> m) { // 计算测试数据m和训练数据i的距离 
	double sum2 = 0;
	for (auto it = train[i].begin(); it != train[i].end(); ++it) // i有的单词 
		sum2 += pow(abs(it->second-m[it->first]),p);
	for (auto it = m.begin(); it != m.end(); ++it) // m有的单词 
		if (train[i].count(it->first) == 0) sum2 += pow(it->second,p); // 防止重复计算 
	return pow(sum2,1.0/p);
}

int main() {
	ifstream infile;
	ofstream outfile;
	int i,n = 0;
	string s,label[6]={"anger","disgust","fear","joy","sad","surprise"};
	vector<int> v;
	v.push_back(0);
	// training...
	infile.open("train_set.csv");
	getline(infile,s);
	while (getline(infile,s)) {
		n++; // 动态计算训练数据个数 
		int l = s.find(','),x = 0;
		string s1 = s.substr(0,l),s2 = s.substr(l+1); // s1：句子，s2：标签
		// split句子
		while (s1.find(' ',x) != string::npos) { 
			train[n][s1.substr(x,s1.find(' ',x)-x)]++;
			x = s1.find(' ',x)+1;
		}
		train[n][s1.substr(x)]++;
		for (i=0; i<6; i++) // 记录该训练数据标签 
			if (s2 == label[i]) {
				v.push_back(i);
				break;
			}
	}
	infile.close();
	
	/* // debug，验证训练集词频是否正确 
	for (i=1; i<=n; i++) {
		for (auto it = train[i].begin(); it != train[i].end(); ++it) cout << it->first << " ";
		cout << endl;
		for (auto it = train[i].begin(); it != train[i].end(); ++it) cout << it->second << " ";
		cout << endl << label[v[i-1]] << endl;
	}
	*/ 
	
	omp_set_num_threads(8); // 设置线程数为 8 
	// validating... 
	infile.open("validation_set.csv"); 
	int xx[6] = {0,0,0,0,0,0};
	int correct=0,sum=0; // 正确数、总数 
	node N[n+1];
	getline(infile,s);
	while (getline(infile,s)) {
		//cout << "Judgeing: " << s << endl;
		sum++; // 动态计算验证集数据个数 
		int l = s.find(','),x = 0;
		unordered_map<string,int> m;
		string s1 = s.substr(0,l),s2 = s.substr(l+1); // s1：句子，s2：标签 
		// split句子
		while (s1.find(' ',x) != string::npos) {
			m[s1.substr(x,s1.find(' ',x)-x)]++;
			x = s1.find(' ',x)+1;
		}
		m[s1.substr(x)]++;
		// 初始化验证数据与训练数据距离 
		for (i=1; i<=n; i++) {
			N[i].index = i;
			N[i].l = 0;
		}
		// 计算距离 
		for (i=1; i<=n; i++) N[i].l = counting(i,m);
		sort(N+1,N+n+1,cmp); // 按距离升序排序 
		// 多数投票 
		int a[6] = {0,0,0,0,0,0},max=0,j;
		for (i=1; i<=k; i++) a[v[N[i].index]]++;
		for (i=0; i<6; i++) 
			if (max < a[i]) {
				max = a[i];
				j = i;
			}
		// 判断验证是否正确 
		// cout << label[j] << " " << s2 << endl; 
		if (label[j] == s2) correct++;
		xx[j]++;
	}
	cout << "验证结果：" << correct << ":" << sum << "(" << correct*100.0/sum << "%)" << endl;
	//cout << xx[0] << " " << xx[1] << " " << xx[2] << " " << xx[3] << " " << xx[4] << " " << xx[5] << " " << endl;
	infile.close();
	
	infile.open("test_set.csv");
	outfile.open("18340146_songyujie_KNN_classification.csv");
	getline(infile,s);
	int xxx[6] = {0,0,0,0,0,0};
	while (getline(infile,s)) {
		int l1 = s.find(',');
		int l2 = s.find(',',l1+1),x = 0;
		string s1 = s.substr(l1+1,l2-l1);// split句子
		unordered_map<string,int> m;
		while (s1.find(' ',x) != string::npos) {
			m[s1.substr(x,s1.find(' ',x)-x)]++;
			x = s1.find(' ',x)+1;
		}
		m[s1.substr(x)]++;
		// 初始化测试数据与训练数据距离 
		for (i=1; i<=n; i++) {
			N[i].index = i;
			N[i].l = 0;
		}
		// 计算距离
		for (i=1; i<=n; i++) N[i].l = counting(i,m);
		sort(N+1,N+n+1,cmp); // 按距离升序排序 
		// 多数投票 
		int a[6] = {0,0,0,0,0,0},max=0,j;
		for (i=1; i<=k; i++) a[v[N[i].index]]++;
		for (i=0; i<6; i++) 
			if (max < a[i]) {
				max = a[i];
				j = i;
			}
		outfile << s.substr(0,l1) << "," << label[j] << endl;
		xxx[j]++;
	}
	//cout << xxx[0] << " " << xxx[1] << " " << xxx[2] << " " << xxx[3] << " " << xxx[4] << " " << xxx[5] << " " << endl;
	infile.close();
	outfile.close();
}
