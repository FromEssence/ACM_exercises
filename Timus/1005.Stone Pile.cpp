/*
* AC 0.015	404 KB
* 枚举每堆石子选或不选
* O(2^20)
*/
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
const int maxn = 128e4;
int sto[26];
int n, sum=0;
int mindif = 1e9;
void dfs(int pos, int tol){
    if(pos==n){
        mindif = min(mindif, (int)abs(sum-tol-tol));
        return;
    }
    dfs(pos+1, tol+sto[pos]);
    dfs(pos+1, tol);
}
int main()
{
    scanf("%d", &n);
    for(int i=0; i<n; i++){
        scanf("%d", &sto[i]);
        sum += sto[i];
    }
    dfs(0, 0);
    printf("%d", mindif);
    return 0;
}
