#include <bits/stdc++.h>
using namespace std;

int main() {
	ifstream infile;
	ofstream outfile;
	infile.open("semeval.txt"); 
	map<int,map<string,int>> TF;
	map<string,int> IDF;
	vector<int> v; // ���ÿ�е����� 
	string s;
	int i,j,c = 0;
	while (getline(infile,s)) {
		c++; // ��̬�������ݸ��� 
		j = 0; // ��̬����ÿ�е��ʸ��� 
		int n = s.find_last_of("\t"); // ǰ����ı���ź������Ȩ������Ч���� 
		int x = n+1;
		while (s.find(' ',x) != string::npos) { // s.split()
			if (TF[c].count(s.substr(x,s.find(' ',x)-x)) == 0) // ĳ��������δ���ֹ�������� 
				IDF[s.substr(x,s.find(' ',x)-x)]++; // IDF++ 
			TF[c][s.substr(x,s.find(' ',x)-x)]++; // TF++
			x = s.find(' ',x)+1;
			j++;
		}
		if (TF[c].count(s.substr(x)) == 0) // ���һ������ 
			IDF[s.substr(x)]++;
		TF[c][s.substr(x)]++;
		v.push_back(j+1);
	}
	int judge = 1; // 1��txt��0��csv 
	if (judge == 1) {
		outfile.open("18340146_songyujie_TFIDF.txt");
		outfile << "TF-IDF" << endl;
		for (auto it = IDF.begin(); it != IDF.end(); ++it) { // ������е��ʣ�map�Դ��ֵ�������
			if (it != IDF.begin()) outfile << " ";
			outfile << it->first;
		}
		outfile << endl;
		for (i=1; i<=c; i++) {
			for (auto it = IDF.begin(); it != IDF.end(); ++it) { // ���ÿ�����ݵ�TF-IDF
				if (it != IDF.begin()) outfile << " ";
				outfile << (double)(TF[i].count(it->first) ? TF[i][it->first] : 0)/v[i-1]*log10((double)c/(it->second+1));
			}
			outfile << endl;
		}
	}
	/* // ����csv�ļ� 
	else {
		outfile.open("18340146_songyujie_TFIDF.csv");
		outfile << "TF-IDF" << endl;
		for (auto it = IDF.begin(); it != IDF.end(); ++it) { // ������е��ʣ�map�Դ��ֵ�������
			if (it != IDF.begin()) outfile << ",";
			outfile << it->first;
		}
		outfile << endl;
		for (i=1; i<=c; i++) {
			for (auto it = IDF.begin(); it != IDF.end(); ++it) { // ���ÿ�����ݵ�TF 
				if (it != IDF.begin()) outfile << ",";
				outfile << (double)(TF[i].count(it->first) ? TF[i][it->first] : 0)/v[i-1]*log10((double)c/(it->second+1));
			}
			outfile << endl;
		}
	}
	// */
	infile.close();
	outfile.close();
}
