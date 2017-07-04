#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
#define MAXN 205
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
			flow+=aug(G,S,0x7FFFFFFF,S,T,n);
		return flow;
	}
}
int G[MAXN][MAXN];
int main()
{
	freopen("ISAP_matrix_data.in","r",stdin);
	int m,n,S,T;
	scanf("%d%d",&m,&n);
	for(int i=1,a,b,w;i<=m;i++)
	{
		scanf("%d%d%d",&a,&b,&w);
		G[a][b]+=w;
	}
	S=1;T=n;
	printf("%d\n",ISAP::sap(G,S,T,n));
	return 0;
}
