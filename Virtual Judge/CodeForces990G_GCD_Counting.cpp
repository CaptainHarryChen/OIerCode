#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
const int MAXN=200005,MAXA=200000;

int n;
int mu[MAXN],pri[MAXN],pcnt;
bool npr[MAXN];

void sieve()
{
	mu[1]=1;npr[1]=true;
	for(int i=2;i<MAXN;i++)
	{
		if(!npr[i])
		{
			pri[++pcnt]=i;
			mu[i]=-1;
		}
		for(int j=1;j<=pcnt&&1LL*pri[j]*i<MAXN;j++)
		{
			npr[i*pri[j]]=true;
			if(i%pri[j]==0)
			{
				mu[i*pri[j]]=0;
				break;
			}
			mu[i*pri[j]]=-mu[i];
		}
	}
}

vector<int> adj[MAXN],node[MAXN];
queue<int> Q;
int a[MAXN];
int vis[MAXN];

int bfs(int st,int d)
{
	Q.push(st);
	vis[st]=d;
	int ret=0;
	while(!Q.empty())
	{
		int u=Q.front();Q.pop();
		ret++;
		for(int i=0;i<(int)adj[u].size();i++)
		{
			int v=adj[u][i];
			if(vis[v]!=d&&a[v]%d==0)
			{
				vis[v]=d;
				Q.push(v);
			}
		}
	}
	return ret;
}

long long h[MAXN],ans[MAXN];

int main()
{
	sieve();
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		node[a[i]].push_back(i);
	}
	for(int i=1,x,y;i<=n-1;i++)
	{
		scanf("%d%d",&x,&y);
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	
	for(int i=1;i<=MAXA;i++)
		for(int j=i;j<=MAXA;j+=i)
			for(int k=0;k<(int)node[j].size();k++)
			{
				int st=node[j][k];
				if(vis[st]!=i)
				{
					int sz=bfs(st,i);
					h[i]+=1LL*sz*(sz+1LL)/2LL;
				}
			}
	for(int i=MAXA;i>=1;i--)
		for(int j=i,k=1;j<=MAXA;j+=i,k++)
			ans[i]+=mu[k]*h[j];
	for(int i=1;i<=MAXA;i++)
		if(ans[i])
			printf("%d %I64d\n",i,ans[i]);
	
	return 0;
}
