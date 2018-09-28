#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=100005,MOD=1000000007;

int n,A[MAXN],deg[MAXN],pre[MAXN];
int cnt[MAXN],dp[MAXN];
int ans=1;
bool vis[MAXN];

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&A[i]);
		deg[A[i]]++;
	}
	for(int i=1;i<=n;i++)
	{
		if(deg[i]>2)
		{puts("0");return 0;}
		if(deg[i]<2||vis[i])
			continue;
		int u=i;
		do
		{
			if(vis[u])
			{puts("0");return 0;}
			vis[u]=true;
			pre[A[u]]=u;
			u=A[u];
		}while(u!=i);
	}
	for(int i=1;i<=n;i++)
		if(deg[i]==0)
		{
			int u=i;
			int len1=0,len2=0;
			while(!vis[u])
			{
				len1++;
				vis[u]=true;
				u=A[u];
			}
			do
			{
				len2++;
				u=pre[u];
			}while(deg[u]!=2);
			if(len2<len1)
			{puts("0");return 0;}
			else if(len2>len1)
				ans=ans*2%MOD;
		}
	for(int i=1;i<=n;i++)
		if(!vis[i])
		{
			int len=0;
			int u=i;
			do
			{
				len++;
				vis[u]=true;
				u=A[u];
			}while(u!=i);
			cnt[len]++;
		}
	for(int i=1;i<=n;i++)
	{
		int mul=1;
		if(i!=1&&i%2==1)
			mul=2;
		dp[0]=1;
		dp[1]=mul;
		for(int j=2;j<=cnt[i];j++)
			dp[j]=(1LL*dp[j-2]*(j-1)%MOD*i%MOD+1LL*dp[j-1]*mul%MOD)%MOD;
		ans=1LL*ans*dp[cnt[i]]%MOD;
	}
	
	printf("%d\n",ans);
	
	return 0;
}
