#include <bits/stdc++.h>
using namespace std;

int main() {
	ifstream infile;
	ofstream outfile;
	infile.open("semeval.txt"); 
	map<int,map<string,int>> TF;
	map<string,int> IDF;
	vector<int> v; // 存放每行单词数 
	string s;
	int i,j,c = 0;
	while (getline(infile,s)) {
		c++; // 动态计算数据个数 
		j = 0; // 动态计算每行单词个数 
		int n = s.find_last_of("\t"); // 前面的文本编号和总情感权重是无效数据 
		int x = n+1;
		while (s.find(' ',x) != string::npos) { // s.split()
			if (TF[c].count(s.substr(x,s.find(' ',x)-x)) == 0) // 某行数据尚未出现过这个单词 
				IDF[s.substr(x,s.find(' ',x)-x)]++; // IDF++ 
			TF[c][s.substr(x,s.find(' ',x)-x)]++; // TF++
			x = s.find(' ',x)+1;
			j++;
		}
		if (TF[c].count(s.substr(x)) == 0) // 最后一个单词 
			IDF[s.substr(x)]++;
		TF[c][s.substr(x)]++;
		v.push_back(j+1);
	}
	int judge = 1; // 1：txt，0：csv 
	if (judge == 1) {
		outfile.open("18340146_songyujie_TFIDF.txt");
		outfile << "TF-IDF" << endl;
		for (auto it = IDF.begin(); it != IDF.end(); ++it) { // 输出所有单词（map自带字典序升序
			if (it != IDF.begin()) outfile << " ";
			outfile << it->first;
		}
		outfile << endl;
		for (i=1; i<=c; i++) {
			for (auto it = IDF.begin(); it != IDF.end(); ++it) { // 输出每行数据的TF-IDF
				if (it != IDF.begin()) outfile << " ";
				outfile << (double)(TF[i].count(it->first) ? TF[i][it->first] : 0)/v[i-1]*log10((double)c/(it->second+1));
			}
			outfile << endl;
		}
	}
	/* // 生成csv文件 
	else {
		outfile.open("18340146_songyujie_TFIDF.csv");
		outfile << "TF-IDF" << endl;
		for (auto it = IDF.begin(); it != IDF.end(); ++it) { // 输出所有单词（map自带字典序升序
			if (it != IDF.begin()) outfile << ",";
			outfile << it->first;
		}
		outfile << endl;
		for (i=1; i<=c; i++) {
			for (auto it = IDF.begin(); it != IDF.end(); ++it) { // 输出每行数据的TF 
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
