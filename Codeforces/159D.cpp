///CF_159D
#include <bits/stdc++.h>

using namespace std;
const int maxn = 2005;
#define ll long long
///
int length[maxn <<1];
int sum_end[maxn <<1];
int getPalindLen(string &str){
	/* initialize*/
	memset(length, 0, sizeof(length));
	int mxlen=0, mxid=0;
	char s2[maxn <<1];
	s2[0]='$';
	int j=1;
	for(int i=0; i<str.size(); i++){

		s2[j++] = '#';
		s2[j++] = str[i];
	}
	s2[j++] = '#';
	s2[j++] = '@';
	/*Manacher*/
	for(int i=1; i<j; i++){
		length[i]=mxid+mxlen>i ? min(length[2*mxid-i], mxid+mxlen-i) : 1;
		while(s2[i-length[i]] == s2[i+length[i]]) ++length[i];
		if(i+length[i]-1 > mxid+mxlen-1){
			mxid = i;
			mxlen = length[i];
		}
	}
   /* mxlen=0;
    for(int i=0; i<j; i++){
        mxlen = max(mxlen, length[i]);
    }
    cout <<"mxlen=" <<mxlen <<"\n";
    */
	return j;
}

long long solve(int n){
	ll res=0;
    memset(sum_end, 0, sizeof(sum_end));
	/* get prifix sum */
	for(int i=1; i<n; i++){
		int j = i&1? 1 : 0;
		for(; j<length[i]; j+=2){
			sum_end[i+j]++;
		}
	}
	for(int i=1; i<n; i++){
		sum_end[i] += sum_end[i-1];
	}
	for(int i=1; i<n; i++){
		int j = i&1? 1 : 0;
		for(; j<length[i]; j+=2){
			res += sum_end[i-j-1];
		}
	}
	return res;
}
int main(){
	string s;
	cin >>s;
	int n = getPalindLen(s);
//	cout <<"n=:" <<n <<'\n';
	cout <<solve(n-1) <<"\n";///!注意，传N-1
	return 0;
}
