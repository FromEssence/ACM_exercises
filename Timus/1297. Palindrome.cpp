/**
Manacher's Algorithm
Find the Longest Palindromic Substring
*/
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

void solve(string& s, int &mx, int &id){
    int p[3000];
    mx=id=0;
    memset(p, 0, sizeof(p));
    for (int i = 1; i<s.size(); i++) {
        p[i] = mx > i ? min(p[2*id-i], mx-i) : 1;
        while (s[i + p[i]] == s[i - p[i]]) p[i]++;
        if (i + p[i] > mx) {
            mx = i + p[i];
            id = i;
        }
    }
    mx=0;
    for(int i=0; i<s.size(); i++){
        if(p[i]>mx ){
            mx=p[i];
            id = i;
        }
    }
}
int main()
{
    string s;
    string s2;
    s2.clear();
    cin >>s;
    s2 += '$';//防止越界
    for(int i=0; i<s.size(); i++){
        s2 += '#';
        s2 += s[i];
    }
    s2 += '#';
    s2 += '@';//与s2[0]要不同，防止越界。（不加也可以，因为访问s2[s2.size()]是'\0'
    int mx=0, id=0;
    solve(s2, mx, id);
    for(int i=id-mx+1; i<=mx+id-1; i++){
        if(s2[i]!='#')
            cout<< s2[i];
    }

    return 0;
}
