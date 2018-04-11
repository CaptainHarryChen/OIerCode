#include<cstdio>
#include<cstring>
using namespace std;
const int MAXN=53;

bool G[MAXN][MAXN];
int a[MAXN],b[MAXN];

bool dfs(int u,int ed)
{
	if(u==ed)
		return true;
	for(int i=0;i<MAXN;i++)
		if(G[u][i])
			if(dfs(i,ed))
				return true;
	return false;
}

int main()
{
	long long ans=0;
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",a+i);
	for(int i=1;i<=n;i++)
		scanf("%d",b+i);
	ans=(1LL<<51LL)-2LL;
	int cnt=0;
	for(int i=50;i>0;i--)
	{
		memset(G,0,sizeof G);
		for(int j=0;j<=50;j++)
			for(int k=1;k<=j;k++)
				if(k!=i&&(ans&(1LL<<(long long)k))!=0)
					G[j][j%k]=true;
		bool flag=true;
		for(int j=1;j<=n;j++)
			if(!dfs(a[j],b[j]))
			{
				flag=false;
				cnt++;
				break;
			}
		if(flag)
			ans^=(1LL<<(long long)i);
	}
	if(cnt==50)
		puts("-1");
	else
		printf("%lld\n",ans);
	
	return 0;
}
