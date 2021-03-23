#include <bits/stdc++.h>
using namespace std;

struct node{
	int index; // 训练数据index 
	double l; // 测试数据与该训练数据的距离 
};

int cmp(node a,node b) {
	return a.l>b.l;
}

int k = 7,q = 1; // 参数 

int n;
unordered_map<int,unordered_map<string,int>> train; // 训练集的词频 
unordered_map<string,int> IDF;
unordered_map<int,vector<double>> v,v2,v3;

double counting(int i,unordered_map<string,int> m) { // 计算测试数据m和训练数据i的距离 
	double sum2 = 0;
	for (auto it = train[i].begin(); it != train[i].end(); ++it)
		sum2 += abs(it->second*log10((double)n/(IDF[it->first]+1))*m[it->first]);
	return sum2/train[i].size()/m.size();
}

int main() {
	ifstream infile;
	ofstream outfile;
	int i,j;
	string s;
	
	// training...
	infile.open("train_set.csv");
	getline(infile,s);
	while (getline(infile,s)) {
		n++; // 动态计算训练数据个数 
		int l = s.find(','),x = 0;
		string s1 = s.substr(0,l),s2 = s.substr(l+1); // s1：句子，s2：概率 
		// split句子
		while (s1.find(' ',x) != string::npos) { 
			int x2 = s1.find(' ',x);
			if (train[n].count(s1.substr(x,x2-x)) == 0) IDF[s1.substr(x,x2-x)]++;
			train[n][s1.substr(x,x2-x)]++; // 词频+1 
			x = x2+1;
		}
		train[n][s1.substr(x)]++;
		x = 0;
		while (s2.find(',',x) != string::npos) {
			v[n].push_back(strtod(s2.substr(x,s2.find(',',x)-x).c_str(),NULL)); // 存储训练数据各标签概率 
			x = s2.find(',',x)+1;
		}
		v[n].push_back(strtod(s2.substr(x).c_str(),NULL));
	}
	infile.close();
	
	/* // debug，验证训练集词频和概率是否正确 
	for (i=1; i<=n; i++) {
		for (auto it = train[i].begin(); it != train[i].end(); ++it) cout << it->first << " ";
		cout << endl;
		for (auto it = train[i].begin(); it != train[i].end(); ++it) cout << it->second << " ";
		cout << endl;
		for (j=0; j<6; j++) cout << v[i][j] << " ";
		cout << endl;
	}
	*/
	
	// validating... 
	infile.open("validation_set.csv");
	node N[n+1];
	int sum=0;
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
		x = 0;
		while (s2.find(',',x) != string::npos) {
			v2[sum].push_back(strtod(s2.substr(x,s2.find(',',x)-x).c_str(),NULL)); // 记录验证集各标签概率 
			x = s2.find(',',x)+1;
		}
		v2[sum].push_back(strtod(s2.substr(x).c_str(),NULL));
		// 初始化验证数据与训练数据距离 
		for (i=1; i<=n; i++) N[i].index = i;
		// 计算距离 
		for (i=1; i<=n; i++) N[i].l = counting(i,m)+0.001;
		sort(N+1,N+n+1,cmp); // 按距离升序排序
		double a[6] = {0,0,0,0,0,0},dis=0;
		for (i=1; i<=k; i++) { // 计算比例 
			dis += N[i].l; // 把比例归一化 
			for (j=0; j<6; j++) a[j] += v[N[i].index][j]*N[i].l;
		}
		for (i=0; i<6; i++) v3[sum].push_back(a[i]/dis); // 记录验证集计算出的概率 
		/*
		for (i=0; i<6; i++) cout << v2[sum][i] << " ";
		cout << endl;
		double num = 0;
		for (i=0; i<6; i++) {
			cout << v3[sum][i] << " ";
			num += v3[sum][i];
		}
		cout << num << endl << endl;
		*/
	}
	// 计算相关系数 
	double COR[6] = {0,0,0,0,0,0},X[6] = {0,0,0,0,0,0},Y[6] = {0,0,0,0,0,0};
	// 计算平均值 X，Y 
	for (i=1; i<=sum; i++)
		for (j=0; j<6; j++) {
			X[j] += v2[i][j];
			Y[j] += v3[i][j];
		}
	for (i=0; i<6; i++) {
		X[i] /= sum;
		Y[i] /= sum;
	}
	// 计算相关系数 
	for (j=0; j<6; j++) {
		double cov=0,w1=0,w2=0;
		for (i=1; i<=sum; i++) {
			cov += (v2[i][j]-X[j])*(v3[i][j]-Y[j]);
			w1 += (v2[i][j]-X[j])*(v2[i][j]-X[j]);
			w2 += (v3[i][j]-Y[j])*(v3[i][j]-Y[j]);
		}
		COR[j] = cov/sqrt(w1*w2);
	}
	cout << "相关系数：" << (COR[0]+COR[1]+COR[2]+COR[3]+COR[4]+COR[5])/6 << endl;
	infile.close();
	
	// testing... 
	infile.open("test_set.csv");
	outfile.open("18340146_songyujie_KNN_regression.csv");
	getline(infile,s);
	while (getline(infile,s)) {
		//cout << "Testing: " << s << endl;
		int l1 = s.find(',');
		int l2 = s.find(',',l1+1),x = 0;
		string s1 = s.substr(l1+1,l2-l1);
		unordered_map<string,int> m;
		// split句子
		while (s1.find(' ',x) != string::npos) {
			m[s1.substr(x,s1.find(' ',x)-x)]++;
			x = s1.find(' ',x)+1;
		}
		m[s1.substr(x)]++;
		x = 0;
		// 初始化验证数据与训练数据距离 
		for (i=1; i<=n; i++) N[i].index = i;
		// 计算距离
		for (i=1; i<=n; i++) N[i].l = counting(i,m)+0.001;
		sort(N+1,N+n+1,cmp); // 按距离升序排序
		double a[6] = {0,0,0,0,0,0},dis=0;
		for (i=1; i<=k; i++) { // 计算比例 
			dis += pow(N[i].l,q); // 把比例归一化 
			for (j=0; j<6; j++) a[j] += v[N[i].index][j]*pow(N[i].l,q);
		}
		outfile << s.substr(0,l2) << "," << setprecision(4) << a[0]/dis << "," << a[1]/dis << "," << a[2]/dis << "," << a[3]/dis << "," << a[4]/dis << "," << a[5]/dis << endl;
	} 
	infile.close();
	outfile.close();
}
