/** ZOJ 1649*/
/*
AC 40MS
Attention: This code takes the situation that there are more than one friend into consideration.
*/
#include <iostream>
#include <cstring>
#include <queue>

using namespace std;
///
#define INF 10000000
const int maxsize = 205;
char gra[maxsize][maxsize];
int mindis[maxsize][maxsize];
int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
struct state{
	int x, y;
	int dis = 0;
	state(){};
	state(int xx, int yy, int d){x=xx, y=yy, dis=d;}
};
///
int main(){
	int n, m;
	int sx, sy, ex, ey;
	while(cin >> n>> m ){
        queue<state> Q;
		while(!Q.empty()) Q.pop();
		for(int i=0; i<maxsize; i++)
		{
			for(int j=0; j<maxsize; j++)
			{
				mindis[i][j] = INF;
			}
		}
		for(int i=0; i<n; i++)
		{
			for(int j=0; j<m; j++)
			{
				cin >> gra[i][j];
				if(gra[i][j] == 'a')
				{
					ex = i, ey=j;
				}
				if(gra[i][j] == 'r')
				{
					sx = i, sy = j;
					mindis[sx][sy] = 0;
					Q.push(state(sx, sy, 0));
				}
			}
		}

		//Q.push(state(sx, sy, 0));
		//int step = 0;
		while(!Q.empty())
		{
			state tmp = Q.front();
			//if(tmp.x == ex && tmp.y == ey)
			//{
			//	mindis[ex][ey] = min(mindis[ex][ey], tmp.dis);
			//}

			for(int k=0; k<4; k++)
			{
				int tmpx = tmp.x + dir[k][0];
				int tmpy = tmp.y + dir[k][1];
				int tmptime = tmp.dis+1;
				//int tmpst = step;
				if(tmpx >= 0 && tmpx < n && tmpy >= 0 && tmpy < m && gra[tmpx][tmpy] != '#')
				{
                    if(gra[tmpx][tmpy] == 'x') tmptime ++;
					if(tmptime < mindis[tmpx][tmpy])
					{
						mindis[tmpx][tmpy] = tmptime;
						Q.push(state(tmpx, tmpy, tmptime));
					}
				}
			}
			Q.pop();
		}
		if(mindis[ex][ey] == INF)
		{
			cout<<"Poor ANGEL has to stay in the prison all his life.\n";
		}
		else cout<< mindis[ex][ey]<<"\n";
	}

	return 0;
}
