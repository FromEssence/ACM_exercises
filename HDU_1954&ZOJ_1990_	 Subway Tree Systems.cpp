/**
AC
HDU_1954&ZOJ_1990_Subway Tree Systems
HASH
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
#define INIT 191
#define P1 701
#define P2 34943
const int maxn=1600;
///
template<int maxn, class T>
struct Tree
{
  struct Node
  {
	  T name;
	  vector<int> son_ind;
	  Node(){son_ind.clear();}
	  Node(T na){name=na;son_ind.clear();}
	  void Add(int pr){son_ind.push_back(pr);}
	  int cntSon(){return son_ind.size();}
  };

	int root;///最小为0
	map<T, int> pos;///节点存储位置的下标
	int nxtpos;///即将分配的节点存储空间
	Node nodes[maxn];///静态节点
	Tree(){root=-1; pos.clear(); nxtpos=0;};
	Tree(int rt){root=rt; pos.clear(); nxtpos=0;}
	bool addEdge(T u, T v)///u是前驱节点
	{
		if(nxtpos==maxn) return false;///空间不足
		if(!pos.count(u)){
			pos[u] = nxtpos++;
			nodes[pos[u]] = Node(u);
		}
		if(nxtpos==maxn) return false;
		if(!pos.count(v)){
			pos[v] = nxtpos++;
			nodes[pos[v]] = Node(v);
		}
		nodes[pos[u]].son_ind.push_back(pos[v]);
		return true;
	}
	void setRt(int rt){root = rt;}
	int getRoot(){return root;}
	int getSize(){return nxtpos;}
	void printTree(){
		if(root==-1){cout <<"Don't know which is root!\n"; return;}
		cout <<"前驱   后继\n";
		for(int i=0; i<nxtpos; i++){
			cout <<nodes[i].name <<' ';
			for(int j=0; j<nodes[i].son_ind.size(); j++)
				cout <<nodes[i].son_ind[j] <<' ';
			cout <<'\n';
		}
	}

};
bool flag;
int cnt;
void dfs_build(char* str, int &len, int& pos, int no, Tree<maxn, int> &tr){
	while(pos < len){
		if(str[pos++]=='1') break;
		tr.addEdge(no, ++cnt);
		dfs_build(str, len, pos, cnt, tr);
	}
	/*sort the tree, so that for each node, the deeper son lies righter*/
	return;
}
int Hash(Tree<maxn, int> &now, int root){
	int value = INIT;
	vector<int> sub;
	// get all Hash value of subtree
	for(size_t i=0; i<now.nodes[root].son_ind.size(); i++){
		sub.push_back(Hash(now, now.nodes[root].son_ind[i]));
	}
	sort(sub.begin(), sub.end());
	for(size_t i=0; i<sub.size(); i++){
		value = ( (value*P1) ^ sub[i] ) % P2;
	}
	return value % P2;
}
int main(){
    int test;
    cin >>test;
    char str1[3005], str2[3005];
    while(test--){
    	Tree<maxn, int> mytree[2];
    	flag = true;
    	scanf("%s%s", str1, str2);
    	int len1 = strlen(str1);
    	int len2 = strlen(str2);
    	if(len1 != len2){
    		cout <<"different\n";
    		continue;
    	}
    	cnt=0;
    	int pos=0;
    	dfs_build(str1, len1, pos, 0, mytree[0]);
    	mytree[0].setRt(mytree[0].pos[0]);
    	cnt=0;
    	pos = 0;
    	dfs_build(str2, len2, pos, 0, mytree[1]);
    	mytree[1].setRt(mytree[1].pos[0]);
    	if(Hash(mytree[0], mytree[0].getRoot()) ==Hash(mytree[1], mytree[1].getRoot()) )
            cout <<"same\n";
        else cout<<"different\n";
    	/*cout <<"1:\n";
    	mytree[0].printTree();*/
    }

return 0;
}
/*

*/
