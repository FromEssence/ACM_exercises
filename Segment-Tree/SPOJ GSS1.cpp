/**SPOJ-GSS1 Can you answer these queries I
 * 最大子段和
 * AC 300ms 22528kB
 */
#include <bits/stdc++.h>
using namespace std;
#define LL long long
#define lson l, m, rt << 1
#define rson m+1, r, rt<<1 | 1
const LL maxn=50005;
struct Val
{
	LL sum, mx, lm, rm; //区间和，左起最大和，右起最大和
	Val(){
		sum=mx=lm=rm=0;
	}
}val[maxn<<2];

void PushUp(LL rt){
	val[rt].sum = val[rt<<1].sum+val[rt<<1|1].sum;
	val[rt].lm = max(val[rt<<1].lm, val[rt<<1].sum+val[rt<<1|1].lm);
	val[rt].rm = max(val[rt<<1|1].rm, val[rt<<1|1].sum+val[rt<<1].rm);
	val[rt].mx = max(max(val[rt<<1].mx, val[rt<<1|1].mx), val[rt<<1].rm+val[rt<<1|1].lm);
}

void build(LL l, LL r, LL rt){
	if(l==r){
		cin >>val[rt].sum;
		val[rt].mx=val[rt].lm=val[rt].rm=val[rt].sum;
		return;
	}
	LL m=(l+r)>>1;
	build(lson);
	build(rson);
	PushUp(rt);
}

Val query(LL L,LL R,LL l,LL r,LL rt){
	if(L==l && r==R) return val[rt];
	LL m=(l+r)>>1;
	if(R<=m) return query(L, R, lson);
	if(L>m) return query(L, R, rson);
	//区间横跨左右孩子
	Val left, right, result;
	left = query(L, m, lson);
	right = query(m+1, R, rson);
	result.sum=left.sum+right.sum;
	result.lm=max(left.lm, left.sum+right.lm);
	result.rm=max(right.rm, right.sum+left.rm);
	result.mx=max(max(left.mx, right.mx), left.rm+right.lm);
	return result;
}

int main(){
	ios::sync_with_stdio(false);
    LL N, M;
    cin >>N;
    build(1, N, 1);
    cin >>M;
    for(int i=0; i<M; i++){
    	int x, y;
    	cin >>x >>y;
    	cout <<query(x, y, 1, N, 1).mx <<'\n';
    }

	return 0;
}
