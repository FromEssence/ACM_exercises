/*
CF_609D Gadgets for dollars and pounds
AC 592 ms	9400 KB
*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn = 2e5+10;
const int MAX = 2e6;
///
ll miney[2][maxn];///record the min in[1, i]
int pre[2][maxn];///record the pos of the min in[1, i]
vector<pair<int, int> > gad[2];
   //price, id
pair<int, int> ans[maxn];
int tot1=0, tot2=0;
ll n, m, k, s;
///
void init(){
    miney[0][0]=miney[1][0] = 2e7;
}

bool judge(int day){
    int p1 = 0, p2=0;
    ll m1 = miney[0][day];
    ll m2 = miney[1][day];
    ll tot = 0;
    for(int i=1; i<=k; i++){
        if(gad[0][p1].first*m1 < gad[1][p2].first*m2){
            tot += gad[0][p1].first*m1;
            ans[i] = make_pair(gad[0][p1].second, pre[0][day]);
           // cout <<"qw" <<gad[0][p1].second <<' ' <<pre[0][day] <<"\n";
            ++p1;
        }
        else{
            tot += gad[1][p2].first*m2;
            ans[i] = make_pair(gad[1][p2].second, pre[1][day]);
           // cout <<"qw" <<gad[1][p2].second <<' ' <<pre[1][day] <<"\n";
            ++p2;
        }
    }
    if(tot <= s) return true;

    return false;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    init();
    cin >>n >>m >>k >>s;
    ll d, p;
    for(int j=0; j<2; j++){
        for(int i=1; i<=n; i++){
            cin >>d;
            if(miney[j][i-1] > d){
                miney[j][i] = d;
                pre[j][i] = i;
            }
            else{
                miney[j][i] = miney[j][i-1];
                pre[j][i] = pre[j][i-1];
            }
        }
    }
    for(int i=1; i<=m; i++){
        cin >>d >>p;
        gad[(d+1)%2].push_back(make_pair(p, i));
    }
    gad[0].push_back(make_pair(MAX, MAX));
    gad[1].push_back(make_pair(MAX, MAX));///便于简化judge函数中的if语句

    sort(gad[0].begin(), gad[0].end());
    sort(gad[1].begin(), gad[1].end());

    int l=1, r=n, mid;
    while(l < r){
        mid = (l+r) >> 1;
        if(judge(mid)) r=mid;
        else l=mid+1;
    }
    if(!judge(l)){
        cout <<"-1\n";
        return 0;
    }
    else{
        cout <<l <<'\n';
       // cout <<pre[0][3] <<'\n';
        for(int i=1; i<=k; i++){
            cout <<ans[i].first <<' ' <<ans[i].second <<'\n';
        }
    }
    return 0;
}
