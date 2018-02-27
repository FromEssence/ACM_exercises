/**CF_474F Ant colony
 * 区间最小值和GCD查询
 * AC 49100 KB	607 ms
 */
#include <bits/stdc++.h>
using namespace std;
#define LL long long
#define lson l, m, rt << 1
#define rson m+1, r, rt<<1 | 1
const LL maxn=500005;
const LL maxVal=1e9;
struct Val
{
	LL minVal, minCnt, gcd; //区间
	Val(){
		minVal=gcd=maxVal;
		gcd=1;
	}
}val[maxn<<2];

LL Gcd(LL a, LL b){
    if(a<b) swap(a, b);
    while(b){
        int  t = b;
        b = a%b;
        a = t;
    }
    return a;
}

void PushUp(LL rt){
    if(val[rt<<1].minVal==val[rt<<1|1].minVal){
        val[rt].minCnt = val[rt<<1].minCnt+val[rt<<1|1].minCnt;
    }
    else if(val[rt<<1].minVal<val[rt<<1|1].minVal){
        val[rt].minCnt = val[rt<<1].minCnt;
    }
    else val[rt].minCnt = val[rt<<1|1].minCnt;
    val[rt].minVal = min(val[rt<<1].minVal, val[rt<<1|1].minVal);
    val[rt].gcd = Gcd(val[rt<<1].gcd, val[rt<<1|1].gcd);
}

void build(LL l, LL r, LL rt){
	if(l==r){
		cin >>val[rt].minVal;
		val[rt].minCnt=1;
		val[rt].gcd = val[rt].minVal;
		return;
	}
	LL m=(l+r)>>1;
	build(lson);
	build(rson);
	PushUp(rt);
}

Val query(LL L,LL R,LL l,LL r,LL rt){
    if(L<=l && r<=R){
        return val[rt];
    }
    int m=(l+r)>>1;
    Val res;
    bool flagL=false;
    if(L<=m){
        flagL=true;
        res=query(L, R, lson);
    }
    if(R>m){
        if(flagL){
            Val tmp=query(L, R, rson);
            if(res.minVal==tmp.minVal) res.minCnt += tmp.minCnt;
            else if(res.minVal>tmp.minVal) {
                res.minCnt = tmp.minCnt;
                res.minVal = tmp.minVal;
            }
            res.gcd = Gcd(res.gcd, tmp.gcd);
        }
        else{
            res=query(L, R, rson);
        }
    }
    return res;
}

int main(){
	ios::sync_with_stdio(false);
	int t;
    LL N, M;
    	cin >>N;
	    build(1, N, 1);
	    cin >>M;
	    for(int i=0; i<M; i++){
            LL l, r;
            cin >>l >>r;
            Val res=query(l, r, 1, N, 1);
            if(res.minVal==res.gcd){
                cout <<r-l+1-res.minCnt <<'\n';
            }
            else cout <<r-l+1 <<'\n';
	    }

	return 0;
}
