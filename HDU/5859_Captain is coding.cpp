/**
*HDU 5859
*AC 530MS	1772K
*二分答案
*
*/
#include <bits/stdc++.h>
using namespace std;

const int maxPro = 1005;
///
struct Problem
{
	int difficulty;
	int inc;
	char c;//类别
	Problem(){};
	Problem(int d, int i, char ch){
		difficulty = d;
		inc = i;
		c = ch;
	}
};

struct Captain
{
	int skill;
	Captain(){skill = 0;}
};

struct cmp
{
	bool operator()(const Problem& p1, const Problem& p2){
		return p1.difficulty > p2.difficulty;
	}
};
struct cmpQ{
	bool operator()(const Problem& p1, const Problem& p2){
		return p1.inc < p2.inc;
	}
};
Problem pros[maxPro];
vector<Problem>q[2];
int n, x, y, w, z;
Captain chen;
///
bool judge(int time){
	//init
	priority_queue<Problem, vector<Problem>, cmpQ> QB;
	while(!QB.empty()) QB.pop();
	q[0].clear();
	q[1].clear();
	for(int i=0; i<n; i++){
		if(pros[i].c == 'A') q[0].emplace_back(pros[i]);
		else q[1].emplace_back(pros[i]);
	}
	///
	sort(q[0].begin(), q[0].end(), cmp());
	sort(q[1].begin(), q[1].end(), cmp());

	int prac_time = time-n;//有prac_time次休息的机会
	int cnt = 0;
	while(cnt <= time){
		while(!q[0].empty() &&  q[0].back().difficulty<=chen.skill){
            if(cnt >= x) return false;/// x
			chen.skill += q[0].back().inc;
			q[0].pop_back();
			cnt++;
		}
			while(!q[1].empty() &&  q[1].back().difficulty<=chen.skill){
				QB.push(q[1].back());
				q[1].pop_back();
			}
			if(q[0].empty() && q[1].empty() && QB.empty()) {///注意要在这里判断，否则因为后面的if-else中逻辑不严谨会出错，
				if(cnt <= time && cnt <= y) return true;///就是下面给出的样例。
				else return false;
			}			//int maxinc;
			if(!QB.empty() && (QB.top().inc >= z || prac_time<=0)){
				chen.skill += QB.top().inc;
				QB.pop();
				cnt++;
			}
			else{
               if(prac_time<=0) return false; //错
                chen.skill += z;
                cnt++;
                prac_time--;
			}
		//}
		//cout <<"break;";

	}
	return false;
}


int main(){
	int Tes;
	cin >>Tes;
	while(Tes--){
		cin >>n >>x >>y >>w >>z;
		chen.skill = w;

		for(int i=0; i<n; i++){
			cin >>pros[i].difficulty >>pros[i].inc;
			getchar();
			pros[i].c = getchar();
			//cout <<"c=" <<pros[i].c<<endl;//test
		}

	// 使时限小的名称改为A；
	if(x>y){
		for(int i=0; i<n; i++){
			pros[i].c = 'A'+'B'-pros[i].c;
		}
		swap(x, y);
	}

	int l = n, r = max(n, y)+1;
	while(l != r){
        chen.skill = w;
		int mid = (l+r) >> 1;
		if(judge(mid)) r = mid;
		else l = mid+1;
	}
	if(l > y){
		cout <<"Poor Captain Chen\n";
	}
	else cout << l <<'\n';
	}

	return 0;
}
/*test

4 5 10 1 1
3 1 A
3 1 A
1 1 B
2 1 B
*/
