/*AC 233 ms	11500 KB
注意分出的段必须包含所有数字，这里用last记录最后一个数字是否已经被分到线段
*/
#include <bits/stdc++.h>
using namespace std;
///
map<int, int> record;
struct seg{
    int inds, inde;
    seg(){};
    seg(int i1, int i2){
        inds = i1;
        inde = i2;
    }
};

vector<seg> segs;
int main(){
    int n;
    int num;
    int preindex = 1;
    int last;
    cin >> n;
    for(int i=1; i<=n; i++)
    {
        scanf("%d", &num);
        if(record.count(num) != 0)
        {
            segs.push_back(seg(preindex, i));
            last = i;
            preindex = i+1;
            record.clear();
        }
        else record[num]++;
    }
    if(segs.size() == 0)
    {
        cout<<-1;
        return 0;
    }
    if(last != n)
        segs.back().inde = n;
    cout<<segs.size()<<'\n';
    for(int i=0; i<segs.size(); i++)
    {
        cout<<segs[i].inds<<' '<<segs[i].inde;
        cout<<'\n';
    }
    return 0;
}
