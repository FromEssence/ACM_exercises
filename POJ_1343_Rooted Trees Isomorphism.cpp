/**
AC_POJ 1343 1984K 110MS	
Rooted Trees Isomorphism 树的同构
*/
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <cstring>
using namespace std;
#define INIT 191
#define P1 701
#define P2 34943
const int maxn=105;
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

	int root;
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
struct cmp{
    bool operator()(const priority_queue<int, vector<int>, greater<int> >&a, const priority_queue<int, vector<int>, greater<int> >& b){
        return a.top() < b.top();
    }
};
int main(){
    Tree<maxn, int> mytree[160];
    map<int, int > grou_ind;
    int n_gro=0;
    vector<priority_queue<int, vector<int>, greater<int> > > grou;
    grou.resize(205);
    int HaVal[200];
    bool used[105];
    int n, k;
    int u, v;
    cin >>k >>n;
    for(int i=0; i<k; i++){
        memset(used, false, sizeof(used));
        for(int j=0; j<n-1; j++){
            scanf("%d%d", &u, &v);
            mytree[i].addEdge(u, v);
            used[v]=true;
        }
        for(int j=1; j<=n; j++){
            if(!used[j]){
                HaVal[i] = Hash(mytree[i], mytree[i].pos[j]);
                if(!grou_ind.count( HaVal[i])) grou_ind[HaVal[i]] = n_gro++;
                grou[grou_ind[HaVal[i]] ].push(i+1);
                break;
            }
        }
    }
    sort(grou.begin(), grou.begin()+n_gro, cmp());
    for(int i=0; i<n_gro; i++){
        int cnt=0;
        while(!grou[i].empty()){
            if(cnt++>0) cout <<" = ";
            cout <<grou[i].top();
            grou[i].pop();
        }
        cout <<" ;\n";
    }


return 0;
}
