#include<cstdio>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<queue>
#define MAXN 205
using namespace std;
int n,m,T;
bool G[MAXN][MAXN],vis[MAXN],color[MAXN];
bool BFS()
{
	queue<int>q;
	q.push(0);
	color[0]=1;
	vis[0]=1;
	while(!q.empty())
	{
		int t=q.front();
		q.pop();
		for(int i=0;i<n;i++)
		{
			if(G[t][i]&&!vis[i])
			{
				vis[i]=1;
				color[i]=!color[t];
				q.push(i);
			}
			else if(G[t][i])
			{
				if(color[t]==color[i])
					return 0;
			}
		}
	}
	return 1;
}
int main()
{
	while(1)
	{
		memset(vis,0,sizeof vis);
		memset(color,0,sizeof color);
		memset(G,0,sizeof G);
		cin>>n;
		if(n==0)break;
		cin>>m;
		for(int i=1,x,y;i<=m;i++)
		{
			cin>>x>>y;
			G[x][y]=1;
			G[y][x]=1;
		}
		if(BFS())
			cout<<"BICOLORABLE"<<endl;
		else
			cout<<"NOT BICOLORABLE"<<endl;
	}
	return 0;
}
