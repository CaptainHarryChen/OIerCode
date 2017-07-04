#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAXN 53
namespace ISAP
{
	int cntd[MAXN],d[MAXN];
	int aug(int G[MAXN][MAXN],int now,int augco,int S,int T,int n)
	{
		int augc=augco,mn=n-1;
		if(now==T)
			return augco;
		for(int i=1,temp;i<=n;i++)
			if(G[now][i]>0)
			{
				if(d[i]==d[now]-1)
				{
					temp=min(augc,G[now][i]);
					temp=aug(G,i,temp,S,T,n);
					G[now][i]-=temp;
					G[i][now]+=temp;
					augc-=temp;
					if(d[S]>=n)return augco-augc;
					if(augc==0)break;
				}
				mn=min(mn,d[i]);
			}
		if(augco==augc)
		{
			cntd[d[now]]--;
			if(cntd[d[now]]==0)
				d[S]=n;
			d[now]=mn+1;
			cntd[d[now]]++;
		}
		return augco-augc;
	}
	int sap(int G[MAXN][MAXN],int S,int T,int n)
	{
		memset(cntd,0,sizeof cntd);
		memset(d,0,sizeof d);
		cntd[0]=n;
		int flow=0;
		while(d[S]<n)
			flow+=aug(G,S,200,S,T,n);
		return flow;
	}
}
int G[MAXN][MAXN];
char str[MAXN][MAXN];
int main()
{
	int n,a1,a2,an,b1,b2,bn,S,T;
	while(~scanf("%d%d%d%d%d%d%d",&n,&a1,&a2,&an,&b1,&b2,&bn))
	{
		memset(G,0,sizeof G);
		memset(str,0,sizeof str);
		a1++;a2++;b1++;b2++;
		for(int i=1;i<=n;i++)
			scanf("%s",str[i]+1);
		S=n+1;T=n+2;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
			{
				if(str[i][j]=='X')G[i][j]=0;
				if(str[i][j]=='O')G[i][j]=2;
				if(str[i][j]=='N')G[i][j]=200;
			}
		G[S][a1]=an*2;G[S][b1]=bn*2;
		G[a2][T]=an*2;G[b2][T]=bn*2;
		if(ISAP::sap(G,S,T,n+2)<(an+bn)*2)
		{printf("No\n");continue;}
		memset(G,0,sizeof G);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
			{
				if(str[i][j]=='X')G[i][j]=0;
				if(str[i][j]=='O')G[i][j]=2;
				if(str[i][j]=='N')G[i][j]=200;
			}
		G[S][a1]=an*2;G[S][b2]=bn*2;
		G[a2][T]=an*2;G[b1][T]=bn*2;
		if(ISAP::sap(G,S,T,n+2)<(an+bn)*2)
		{printf("No\n");continue;}
		printf("Yes\n");
	}
	return 0;
}
