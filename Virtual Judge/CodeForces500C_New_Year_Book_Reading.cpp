#include<cstdio>
const int MAXN=505,MAXM=1005;

int n,m;
int w[MAXN],b[MAXM];
bool vis[MAXN];

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",w+i);
	for(int i=1;i<=m;i++)
		scanf("%d",b+i);
	long long ans=0;
	for(int i=1;i<=m;i++)
	{
		for(int j=1;j<=n;j++)
			vis[j]=false;
		for(int j=i-1;j>0&&b[j]!=b[i];j--)
			if(!vis[b[j]])
				ans+=w[b[j]],vis[b[j]]=true;
	}
	printf("%lld\n",ans);
	return 0;
}
