/**
* 13259 - Soccer Championship
* AC 140 ms
*/
/*
* 本人错过的地方：
* 1.比较胜负时用的是分数的字符串形式，虽然能过部分样例。
  2.最初用自己不熟悉的stringstream将string转成int，遇到不懂的错误.
  3.自定义比较函数时写成
   bool operator()(const TeamInfo& t1, const TeamInfo& t2){
                if(t1.r1>t2.r1) return true;
                    ...
                return t1.name < t2.name;
            }
*/
#include <bits/stdc++.h>
using namespace std;
const int maxTeam = 130;
///
struct Match{
	string localname;
	int localgoal;
	string visitname;
	int visitgoal;

	string winner, loser;
    int strTonum(string str){
        int res=0;
        for(int i=0; i<str.size(); i++){
            res *= 10;
            res += str[i]-'0';

        }
        return res;
    }

	Match(string ln, string lg, string vn, string vg){
		localname = ln;
		visitname = vn;

		localgoal = strTonum(lg);
		//cout <<"lg" <<localgoal <<"\n";
		visitgoal = strTonum(vg);
		//cout <<"vg" <<visitgoal <<"\n";

		if(localgoal > visitgoal){
			winner = localname;
			loser = vn;
		}
		else if(localgoal < visitgoal) winner = visitname, loser = ln;
		else winner = "draw", loser = "draw";
	}
	string getWinner(){
		return winner;
	}

	string getLoser(){
		return loser;
	}
	Match(){}
};

struct TeamInfo
{
	string name;
	vector<int> itsMatches;//它参与过的比赛
	int r1, r2, r3, r4;///四部分分数
	int score;
	TeamInfo(){
		itsMatches.clear();
		score = r1=r2=r3=r4=0;
	}
	void setName(string n){
		name = n;
	}
	void addMatch(int pos){//添加比赛
		itsMatches.push_back(pos);
	}

	int getScore(){
		score = r1+r2+r3+r4;
		return score;
	}

	void modifyR1(int s){
		r1 += s;
	}
	void modifyR2(int s){
		r2 += s;
	}
	void modifyR3(int s){
		r3 += s;
	}
	void modifyR4(int s){
		r4 += s;
	}

};

Match matches[maxTeam];///from index 1
int M;
//vector<string > RANK;///final rank
vector<TeamInfo> tmp;
int paradox;
map<string, TeamInfo> team;
map<string, int> RANK;
void init(){
	paradox = 0;
	RANK.clear();
	team.clear();
}

void input(int pos){
	vector<string> Stack;
	Stack.clear();
	string in;
	string ln, lg, vn, vg;
	ln.clear(), lg.clear(), vn.clear(), vg.clear();
	cin >>in;
	while(in!="vs."){
        //cout <<"in=" <<in <<"\n";
		Stack.push_back(in);
        cin >>in;
	}
	lg = Stack.back();
	Stack.pop_back();

	for(int i=0; i<Stack.size(); i++){
		if(i>0) ln += " ";
		ln += Stack[i];
	}

	cin >>vg;
	getchar();
	getline(cin, vn);///稍后检查是否开头多空格

	matches[pos] = Match(ln, lg, vn, vg);
	//cout <<lg <<' ' <<vg <<'\n';
	team[ln].setName(ln);
	team[vn].setName(vn);

	team[ln].addMatch(pos);
	team[vn].addMatch(pos);
    /* r1, r2*/
	if(matches[pos].getWinner() == ln){
		team[ln].modifyR1(3);
		team[ln].modifyR2(abs(matches[pos].localgoal-matches[pos].visitgoal));
		team[vn].modifyR2( - abs(matches[pos].localgoal-matches[pos].visitgoal));
	}
	else if(matches[pos].getWinner() == vn){
		team[vn].modifyR1(3);
		team[ln].modifyR2( - abs(matches[pos].localgoal-matches[pos].visitgoal));
		team[vn].modifyR2( abs(matches[pos].localgoal-matches[pos].visitgoal));
	}
	else{
		team[ln].modifyR1(1);
		team[vn].modifyR1(1);
	}
	//r1 r2 end
	/* r3 */
	team[ln].modifyR3(matches[pos].localgoal);
	team[vn].modifyR3(matches[pos].visitgoal);
	//r3 end

	/* r4*/
	team[vn].modifyR4(matches[pos].visitgoal);
	//r4 end
}


void calRank(){

	tmp.clear();
	for(map<string, TeamInfo>::iterator it = team.begin(); it != team.end(); ++it){
		tmp.emplace_back(it->second);
	}
	struct cmp
		{
			bool operator()(const TeamInfo& t1, const TeamInfo& t2){
				if(t1.r1>t2.r1) return true;
				else if(t1.r1<t2.r1) return false;
				if(t1.r2>t2.r2) return true;
				else if(t1.r2<t2.r2) return false;
				if(t1.r3>t2.r3) return true;
				else if(t1.r3<t2.r3) return false;
				if(t1.r4>t2.r4) return true;
				else if(t1.r4<t2.r4) return false;
				return t1.name < t2.name;
			}
		};
	sort(tmp.begin(), tmp.end(), cmp());
	for(int i=0; i<tmp.size(); i++){
		RANK[tmp[i].name] = i;
		/*printf("******************\n");
		cout <<tmp[i].name <<' ' <<tmp[i].r1 << ' ' <<tmp[i].r2 <<' ' <<tmp[i].r3 <<' '<<tmp[i].r4 <<'\n';
		printf("******************\n");
		*/



	}
	for(int i=1; i<=M; i++){
		string lo = matches[i].getLoser();
		if(lo == "draw") continue;
		if(RANK[lo] < RANK[matches[i].getWinner()]){///! <
          //  cout <<"paradox" <<matches[i].getWinner() <<' '<<matches[i].getLoser() <<'\n';
			paradox++;
		}
	}
}

void printRank(){
	for(int i=0; i<tmp.size(); i++){
		cout <<i+1 <<". " <<tmp[i].name <<'\n';
	}
}
int main(){
   // cout <<("abc"<"bc");
	while(scanf("%d", &M)!=EOF){
		init();
		for(int i=0; i<M; i++){
			input(i+1);
		}
		calRank();
        printf("The paradox occurs %d time(s).\n", paradox);
        printRank();

	}

}
