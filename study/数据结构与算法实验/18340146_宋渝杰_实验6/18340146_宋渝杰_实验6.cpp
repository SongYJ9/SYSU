#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <stack>
 
using namespace std;

struct node{ // 邻接表节点
    string name; // 节点名字
    int l; // 与头节点的距离
    node* next;
};

int main()
{
    vector<string> arr; // 保存图的顶点
    vector<vector<int> > matrix; // 邻接矩阵
    vector<node*> arr2; // 邻接表
    while(true){
        cout<<endl<<"        菜单:"<<endl;
        cout<<"           1: 构造图/添加边"<<endl;
        cout<<"           2: 展示邻接矩阵和邻接表"<<endl;
        cout<<"           3: 深度优先/广度优先遍历"<<endl;
        cout<<"           4: 最短路径计算"<<endl;
        cout<<"           5: 退出"<<endl;
        cout<<"           请输入指令： ";
        string a;
        cin>>a;
        if(a == "1"){ // 创造图/添加边
            int t,i,j;
            if(arr.size() == 0) cout<<"   请输入图的边的条数："<<endl;
            else cout<<"   请输入添加边的条数："<<endl;
            cin>>t;
            for(i=0;i<t;i++){
                cout<<"   请输入两个顶点的名称以及边长："<<endl;
                string str1,str2;
                int l,x = -1,y = -1,a=0,b=0;
                cin>>str1>>str2>>l;
                for(j=0;j<arr.size();j++){ // 寻找第一个节点是否存在
                    if(arr[j] == str1){
                        x = j;
                        break;
                    }
                }
                if(x == -1){ // 如果不存在，则新建一个节点，扩展邻接矩阵和邻接表
                    x = arr.size();
                    vector<int> vec;
                    for(j=0;j<x;j++){
                        vec.push_back(0);
                        matrix[j].push_back(0);
                    }
                    vec.push_back(0);
                    arr.push_back(str1);
                    node* n = new node();
                    n->name = str1;
                    n->l = 0;
                    n->next = NULL;
                    arr2.push_back(n);
                    matrix.push_back(vec);
                }
                for(j=0;j<arr.size();j++){ // 寻找第二个节点是否存在
                    if(arr[j] == str2){
                        y = j;
                        break;
                    }
                }
                if(y == -1){ // 如果不存在，则新建一个节点，扩展邻接矩阵和邻接表
                    y = arr.size();
                    vector<int> vec;
                    for(j=0;j<y;j++){
                        vec.push_back(0);
                        matrix[j].push_back(0);
                    }
                    vec.push_back(0);
                    arr.push_back(str2);
                    node* n = new node();
                    n->name = str2;
                    n->l = 0;
                    n->next = NULL;
                    arr2.push_back(n);
                    matrix.push_back(vec);
                }
                // 建立邻接矩阵
                matrix[x][y] = matrix[y][x] = l;
                // 建立邻接表
                node * n = arr2[x];
                while(n){
                    if(n->name == str2) a = 1;
                    if(n->next == NULL) break;
                    n = n->next;
                }
                if(!a){ // 防止重复
                    node* p = new node();
                    p->name = str2;
                    p->l = l;
                    p->next = NULL;
                    n->next = p;
                }
                n = arr2[y];
                while(n){
                    if(n->name == str1) b = 1;
                    if(n->next == NULL) break;
                    n = n->next;
                }
                if(!b){ // 防止重复
                    node* p = new node();
                    p->name = str1;
                    p->l = l;
                    p->next = NULL;
                    n->next = p;
                }
            }
            cout<<"   输入成功！"<<endl<<endl;
        }
        else if(a == "2"){ // 展示邻接矩阵和邻接表
            if(arr.size()){
                int i,j;
                // 展示邻接矩阵
                cout<<"   邻接矩阵："<<endl<<"      ";
                for(i=0;i<arr.size();i++){
                    cout<<right<<setw(6)<<arr[i];
                }
                cout<<endl;
                for(i=0;i<arr.size();i++){
                    cout<<right<<setw(6)<<arr[i];
                    for(j=0;j<arr.size();j++){
                        if(i != j and matrix[i][j] == 0) cout<<right<<setw(6)<<-1;
                        else cout<<right<<setw(6)<<matrix[i][j];
                    }
                    cout<<endl;
                }
                // 展示邻接表
                cout<<endl<<endl<<"   邻接表："<<endl;
                for(i=0;i<arr.size();i++){
                    cout<<right<<setw(6)<<arr2[i]->name;
                    node* p = arr2[i]->next;
                    while(p){
                        cout<<" -->"<<right<<setw(6)<<p->name;
                        p = p->next;
                    }
                    cout<<endl;
                }
            }
            else cout<<"   尚未构建图！"<<endl;
        }
        else if(a == "3"){
            if(arr.size()){
                vector<int> judge,v;
                stack<int> s;
                int i,j;
                for(i=0;i<arr.size();i++){
                    judge.push_back(0);
                }
                // 深度优先遍历
                cout<<"   DFS: "<<endl;
                cout<<right<<setw(6)<<arr[0];
                s.push(0);
                judge[0] = 1;
                th:;
                for(i=s.top();s.size();i=s.top()){
                    for(j=0;j<arr.size();j++){
                        if(matrix[i][j] != 0 and judge[j] == 0){
                            cout<<right<<setw(6)<<arr[j];
                            judge[j] = 1;
                            s.push(j);
                            goto th;
                        }
                    }
                    s.pop();
                    if(!s.size()) break;
                }
                for(i=0;i<judge.size();i++){
                    judge[i] = 0;
                }
                // 广度优先遍历
                cout<<endl<<"   BFS: "<<endl;
                cout<<right<<setw(6)<<arr[0];
                v.push_back(0);
                judge[0] = 1;
                for(i=0;i<v.size();i++){
                    int k = v[i];
                    for(j=k+1;j<arr.size();j++){
                        if(matrix[k][j] != 0 and judge[j] == 0){
                            cout<<right<<setw(6)<<arr[j];
                            v.push_back(j);
                            judge[j] = 1;
                        }
                    }
                }
                cout<<endl;
            }
            else cout<<"   尚未构建图！"<<endl;
        }
        else if(a == "4"){
            string str1,str2;
            cout<<"   请输入两个顶点： ";
            tt:;
            cin>>str1>>str2;
            int i,j,x=-1,y=-1;
            for(j=0;j<arr.size();j++){
                if(arr[j] == str1){
                    x = j;
                    break;
                }
            }
            for(j=0;j<arr.size();j++){
                if(arr[j] == str2){
                    y = j;
                    break;
                }
            }
            if(x != -1 and y != -1){ // 狄杰斯特拉算法
                int n = arr.size();
                int a[n][n];
                for(i=0;i<n;i++){
                    for(j=0;j<n;j++){
                        if(matrix[i][j] == 0) a[i][j] = 10000;
                        else a[i][j] = matrix[i][j];
                    }
                }
                int dij[n],vis[n];
                for (int i=0; i<n; i++) {
                    dij[i] = a[x][i];
                    vis[i] = (i == x ? 1 : 0);
                }
                for (int i=0; i<n-1; i++) {
                    int mi = 1e7, index = -1;
                    for (int j=0; j<n; j++) {
                        if (vis[j] == 0 and dij[j] < mi) {
                            mi = dij[j];
                            index = j;
                        }
                    }
                    vis[index] = 1;
                    for (int j=0; j<n; j++) dij[j] = min(dij[j], dij[index]+a[index][j]);
                }
                cout<<"   两顶点的最短距离为： "<<dij[y]<<endl;
                /*
                int i,j,min=10000,min2,min3=1;
                int b[n],c[n];
                for(i=0;i<n;i++)
                {
                    b[i]=0;
                    c[i]=0;
                }
                for(i=0;i<n;i++)
                {   c[i]=1;
                    for(j=0;j<n;j++) b[j]=a[i][j];
                    td:;
                    for(j=0;j<n;j++)
                    {   if(c[j]==1) continue;
                        if(b[j]<min)
                        {   min=b[j];
                            min2=j;
                        }
                    }
                    min3++;
                    if(min3>n)
                    {   min3=1;
                        for(j=0;j<n;j++) c[j]=0;
                        goto tu;
                    }
                    min=1000;
                    c[min2]=1;
                    for(j=0;j<n;j++)
                    {   if(a[i][min2]+a[min2][j]<a[i][j])
                        {   a[i][j]=a[i][min2]+a[min2][j];
                            a[j][i]=a[i][j];
                            b[j]=a[i][min2]+a[min2][j];
                        }
                    }
                    goto td;
                    tu:;
                }
                for(i=0;i<n;i++)
                   for(j=0;j<n;j++)
                        if(i==j) a[i][j]=0;
                cout<<"   两顶点的最短距离为： "<<a[x][y]<<endl;
                */
            }
            else{
                cout<<"   顶点不存在！请重新输入：";
                goto tt;
            }
        }
        else if(a == "5"){
            break;
        }
        else{
            cout<<"   输入错误！请重新输入！"<<endl;
        }
    }
}

