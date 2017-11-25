/**
*1014.Product of Digits
*Accepted
*0.001	252 KB
*/
#include <cstdio>
using namespace std;
///
int n;
long long solve(int num){
    if(num==0) return 10;
    if(num==1) return 1;

    long long ans=0;
    long long p=1; /// 注意：p要设为long long
    for(int div = 9; div>1; div--){
        while(n % div==0){
            ans += p*div;
            p *= 10;
            n /= div;
        }
    }
    return (n==1) ? ans : -1;

}
int main(){
    scanf("%d", &n);
    printf("%I64d", solve(n));
}
