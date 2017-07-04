#include<cstdio>
#include<iostream>
#include<queue>
using namespace std;
queue<int>q;
int n,m,s;
bool a[205][205],f[205];
void bfs(int k)
{
	q.push(k);
	while(!q.empty())
	{
		int t=q.front();
		if(f[t]==1)
		{
			q.pop();
			continue;
		}
		f[t]=1;
		s++;
		if(s==n)
			printf("%d",t+1);
		else
			printf("%d ",t+1);
		q.pop();
		for(int i=0;i<n;i++)
			if(a[t][i]==1&&f[i]==0)
				q.push(i);
	}
}
int main()
{
	cin>>n>>m;
	int x,y;
	for(int i=0;i<m;i++)
	{
		scanf("%d%d",&x,&y);
		a[x-1][y-1]=1;
	}
	for(int i=0;i<n;i++)
		if(f[i]==0)
			bfs(i);
	return 0;
}
