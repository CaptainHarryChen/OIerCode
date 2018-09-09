#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=10010;

int prime[MAXN],pcnt;
bool npr[MAXN];

bool vis[MAXN];
int pfac[MAXN],tp;
int ans;

void dfs(int c,int m,int n)
{
	if(c>tp)
	{
		if(m!=1)
		{
			m++;
			for(int i=1;1LL*prime[i]*prime[i]<=m;i++)
				if(m%prime[i]==0)
					return;
			for(int i=1;i<=tp;i++)
				if(prime[pfac[i]]==m&&vis[i])
					return;
		}
		ans=min(1LL*ans,1LL*m*n);
		return;
	}
	dfs(c+1,m,n);
	if(m%(prime[pfac[c]]-1)==0)
	{
		vis[c]=true;
		m/=(prime[pfac[c]]-1);
		n*=prime[pfac[c]];
		dfs(c+1,m,n);
		while(m%prime[pfac[c]]==0)
		{
			m/=prime[pfac[c]];
			n*=prime[pfac[c]];
			dfs(c+1,m,n);
		}
		vis[c]=false;
	}
}

int main()
{
	npr[1]=true;
	for(int i=2;i<MAXN;i++)
	{
		if(!npr[i])
			prime[++pcnt]=i;
		for(int j=1;j<=pcnt&&1LL*prime[j]*i<MAXN;j++)
		{
			npr[i*prime[j]]=true;
			if(i%prime[j]==0)
				break;
		}
	}

	for(int test=1;;test++)
	{
		int m;
		scanf("%d",&m);
		if(m==0)
			break;
		tp=0;
		for(int i=1;1LL*(prime[i]-1)*(prime[i]-1)<=m;i++)
			if(m%(prime[i]-1)==0)
				pfac[++tp]=i;
		ans=0x7FFFFFFF;
		dfs(1,m,1);
		printf("Case %d: %d %d\n",test,m,ans);
	}

	return 0;
}
