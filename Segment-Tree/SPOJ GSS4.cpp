/**SPOJ GSS4 Can you answer these queries IV
 * AC 	19456 KB	320 ms
 * 单点更新，区间求和；剪枝
 */
#include <bits/stdc++.h>
using namespace std;
#define LL long long
#define lson l, m, rt << 1
#define rson m+1, r, rt<<1 | 1
const LL maxn=100005;
LL Val[maxn<<2];
void PushUp(LL rt){
	Val[rt] = Val[rt<<1]+Val[rt<<1|1];
}

void build(LL l, LL r, LL rt){
	if(l==r){
		cin >>Val[rt];
		return;
	}
	LL m=(l+r)>>1;
	build(lson);
	build(rson);
	PushUp(rt);
}

void update(LL L,LL R,LL l,LL r,LL rt){
	//[L,R]是更新的区间，[l,r]是节点rt表示的区间
	if(Val[rt] == r-l+1){
		return ; //无需更新
	}
	if(l==r){
        Val[rt] = floor((double)(sqrt(Val[rt])));
        return ;
	}
	LL m=(l+r)>>1;
	if(L <= m) update(L, R, lson);
	if(R > m)  update(L, R, rson);
	PushUp(rt);
}

LL query(LL L,LL R,LL l,LL r,LL rt){
	if(L<=l && r<=R) return Val[rt];
	LL m=(l+r)>>1;
	LL ret =0;
	if(L<=m) ret += query(L, R, lson);
	if(m<R) ret += query(L, R, rson);
	return ret;
}
int main(){
	ios::sync_with_stdio(false);
    LL N, M, op, l, r;
    LL cnt=0;
    while(cin >>N){
        cnt++;
        cout <<"Case #" <<cnt <<":\n";
        build(1, N, 1);
        cin >>M;
        for(LL i=0; i<M; i++){
            cin >>op >>l >>r;
            if(l>r) swap(l, r);
            if(op==0){
                update(l, r, 1, N, 1);
            }
            if(op==1){
                cout <<query(l, r, 1, N, 1) <<'\n';
            }
        }
        cout <<'\n';
    }


	return 0;
}
