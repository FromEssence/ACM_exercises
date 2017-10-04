/** Stars*/
/*统计左下方二维点的个数
这里使用隐式二叉排序树
*/
#include <cstdio>
#include <map>
#include <algorithm>
const int maxn = 16000;
#define PINT pair<int, int>
using namespace std;
///
PINT star_1[maxn];
PINT star_2[maxn];
int ans[maxn];
int zuoxia[maxn];

int n;
///
struct cmp
{
	bool operator()(const PINT& a, const PINT& b){
		return (a.first < b.first || (a.first==b.first && a.second < b.second));
	}
};
int main(){
	scanf("%d", &n);
	int x, y;
	for(int i=0; i<n; i++){
		scanf("%d%d", &x, &y);
		star_1[i].first = star_2[i].first=x;
		star_1[i].second = star_2[i].second=y;
	}
	sort(star_2, star_2+n, cmp());

	for(int i=0; i<n; i++){
		int l=0, r=n-1;
		int mid ;
		int tmp=0;
		while(l <= r){
			mid = (l+r)/2;
			if(star_2[mid] < star_1[i] ){
				tmp += zuoxia[mid];
				l = mid+1;
			}
			else{
				zuoxia[mid]++;
				r = mid-1;
			}
		}
		ans[tmp]++;
	}

	for(int i=0; i<n; i++){
		printf("%d\n", ans[i]);
	}
	return 0;
}
