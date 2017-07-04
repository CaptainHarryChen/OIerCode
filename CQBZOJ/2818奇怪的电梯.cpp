#include<cstdio>
#include<iostream>
#include<queue>
using namespace std;
int a,b,n,k[10005][2];
bool f[10005];
bool f_(int x)
{
	if(x>0&&x<=n)return 1;
	return 0;
}
int bfs(int x1,int x2)
{
	if(x1==x2)
		return 0;
	int a=x1,cnt=0;
	f[x1]=1;
	queue<int>q;
	q.push(a);
	while(!q.empty())
	{
		int tt=q.front();
		q.pop();
		cnt++;
		for(int i=0;i<2;i++)
		{
			int t=tt;
			t+=k[t][i];
			if(f_(t)&&f[t]!=1)
			{
				if(t==x2)
					return cnt;
				f[t]=1;
				q.push(t);
			}
		}
	}
	return -1;
}
int main()
{
	cin>>n>>a>>b;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&k[i][0]);
		k[i][1]=-k[i][0];
	}
	cout<<bfs(a,b)<<endl;
	return 0;
}
