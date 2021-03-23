#include <bits/stdc++.h>
using namespace std;

struct node{
	int index; // ѵ������index 
	double l; // �����������ѵ�����ݵľ��� 
};

int cmp(node a,node b) {
	return a.l>b.l; // ���ƶȽ������� 
}

int k = 18,q = 2; // ���� 

int n;
unordered_map<int,unordered_map<string,double>> train; // ѵ�����Ĵ�Ƶ 
unordered_map<string,int> IDF; // �����ĵ�Ƶ��

double counting(int i,unordered_map<string,int> m) { // �����������m��ѵ������i�����ƶ�
	double sum2 = 0;
	for (auto it = train[i].begin(); it != train[i].end(); ++it)
		sum2 += abs(it->second*log10((double)n/(IDF[it->first]+1))*m[it->first]);
	return sum2/train[i].size()/m.size();
}

int main() {
	ifstream infile;
	ofstream outfile;
	int i,j;
	string s,label[6]={"anger","disgust","fear","joy","sad","surprise"};
	vector<int> v(1);
	// training...
	infile.open("train_set.csv");
	getline(infile,s);
	while (getline(infile,s)) {
		n++; // ��̬����ѵ�����ݸ��� 
		int l = s.find(','),x = 0,num = 0;
		string s1 = s.substr(0,l),s2 = s.substr(l+1); // s1�����ӣ�s2����ǩ
		// split����
		while (s1.find(' ',x) != string::npos) {
			int x2 = s1.find(' ',x);
			if (train[n].count(s1.substr(x,x2-x)) == 0) IDF[s1.substr(x,x2-x)]++;
			train[n][s1.substr(x,x2-x)]++;
			x = x2+1;
			num++; // ��̬��������ݵ����� 
		}
		train[n][s1.substr(x)]++;
		//for (auto it = train[n].begin(); it != train[n].end(); ++it) it->second /= (num+1); // TF�������� 
		for (i=0; i<6; i++) // ��¼��ѵ�����ݱ�ǩ 
			if (s2 == label[i]) {
				v.push_back(i);
				break;
			}
	}
	infile.close();
	
	/* // debug����֤ѵ������Ƶ�Ƿ���ȷ 
	for (i=1; i<=n; i++) {
		for (auto it = train[i].begin(); it != train[i].end(); ++it) cout << it->first << " ";
		cout << endl;
		for (auto it = train[i].begin(); it != train[i].end(); ++it) cout << it->second << " ";
		cout << endl << label[v[i-1]] << endl;
	}
	*/ 
	
	// validating... 
	infile.open("validation_set.csv"); 
	int xx[6] = {0,0,0,0,0,0};
	int correct=0,sum=0; // ��ȷ�������� 
	node N[n+1];
	getline(infile,s);
	while (getline(infile,s)) {
		//cout << "Judgeing: " << s << endl;
		sum++; // ��̬������֤�����ݸ��� 
		int l = s.find(','),x = 0,num = 0;
		unordered_map<string,int> m;
		string s1 = s.substr(0,l),s2 = s.substr(l+1); // s1�����ӣ�s2����ǩ 
		// split����
		while (s1.find(' ',x) != string::npos) {
			int x2 = s1.find(' ',x);
			m[s1.substr(x,x2-x)]++;
			x = x2+1;
			num++;
		}
		m[s1.substr(x)]++;
		//for (auto it = m.begin(); it != m.end(); ++it) it->second /= (num+1);
		for (i=1; i<=n; i++) N[i].index = i;
		// ������� 
		for (i=1; i<=n; i++) N[i].l = counting(i,m);
		sort(N+1,N+n+1,cmp); // �������������� 
		// ����ͶƱ 
		double a[6] = {0,0,0,0,0,0},max=0;
		for (i=1; i<=k; i++) a[v[N[i].index]] += pow(N[i].l,q);
		for (i=0; i<6; i++) 
			if (max < a[i]) {
				max = a[i];
				j = i;
			}
		// �ж���֤�Ƿ���ȷ 
		// cout << label[j] << " " << s2 << endl; 
		if (label[j] == s2) correct++;
		xx[j]++;
	}
	cout << "��֤�����" << correct << ":" << sum << "(" << correct*100.0/sum << "%)" << endl;
	//cout << xx[0] << " " << xx[1] << " " << xx[2] << " " << xx[3] << " " << xx[4] << " " << xx[5] << " " << endl;
	infile.close();
	
	infile.open("test_set.csv");
	outfile.open("18340146_songyujie_KNN_classification.csv");
	getline(infile,s);
	int xxx[6] = {0,0,0,0,0,0};
	while (getline(infile,s)) {
		int l1 = s.find(',');
		int l2 = s.find(',',l1+1),x = 0;
		string s1 = s.substr(l1+1,l2-l1);// split����
		unordered_map<string,int> m;
		while (s1.find(' ',x) != string::npos) {
			m[s1.substr(x,s1.find(' ',x)-x)]++;
			x = s1.find(' ',x)+1;
		}
		m[s1.substr(x)]++;
		for (i=1; i<=n; i++) N[i].index = i;
		// �������
		for (i=1; i<=n; i++) N[i].l = counting(i,m);
		sort(N+1,N+n+1,cmp); // �������������� 
		// ����ͶƱ 
		double a[6] = {0,0,0,0,0,0},max=0;
		for (i=1; i<=k; i++) a[v[N[i].index]] += pow(N[i].l,q);
		for (i=0; i<6; i++) 
			if (max < a[i]) {
				max = a[i];
				j = i;
			}
		outfile << s.substr(0,l2) << "," << label[j] << endl;
		//xxx[j]++;
	}
	//cout << xxx[0] << " " << xxx[1] << " " << xxx[2] << " " << xxx[3] << " " << xxx[4] << " " << xxx[5] << " " << endl;
	infile.close();
	outfile.close();
}
