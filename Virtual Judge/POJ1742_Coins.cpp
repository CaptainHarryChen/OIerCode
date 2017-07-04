#include<cstdio>
#include<bitset>
using namespace std;
#define MAXN 105
#define MAXM 100005
int n,m;
bitset<MAXM>vis;
int v[MAXN],c[MAXN];
int main()
{
	while(1)
	{
		scanf("%d%d",&n,&m);
		if(!n&&!m)break;
		for(int i=1;i<=n;i++)
			scanf("%d",v+i);
		for(int i=1;i<=n;i++)
			scanf("%d",c+i);
		vis.reset();
		vis[0]=1;
		for(int i=1;i<=n;i++)
		{
			int j=1;
			while(j<c[i])
			{
				vis|=vis<<(j*v[i]);
				c[i]-=j;
				j<<=1;
			}
			vis|=vis<<(v[i]*c[i]);
		}
		int ans=0;
		for(int i=1;i<=m;i++)
			ans+=vis[i];
		printf("%d\n",ans);
	}
	return 0;
}
