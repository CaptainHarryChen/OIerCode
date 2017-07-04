#include<cstdio>
#include<queue>
#include<cstring>
using std::min;
#define MAXN 60
#define INF 0x7FFFFFFF
int N,M,S,T,n;
int G[MAXN][MAXN];
int d[MAXN],cntd[MAXN];
int Read()
{
	int a=0;char str[10];
	scanf("%s",str);
	if(str[0]=='+')a=N+1;
	else if(str[0]=='-')a=N+2;
	else {for(int i=0;str[i];i++)a=a*10+str[i]-'0';}
	return a;
}
int aug(int now,int augco)
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
				temp=aug(i,temp);
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
int sap()
{
	memset(cntd,0,sizeof cntd);
	memset(d,0,sizeof d);
	int flow=0;
	cntd[0]=n;
	while(d[S]<n)
		flow+=aug(S,0x7FFFFFFF);
	return flow;
}
bool check(int flow)
{
	for(int i=1;i<=n;i++)
		if(G[S][i]>0)
			return 0;
	for(int i=1;i<=n;i++)
		if(G[i][T]>0)
			return 0;
	return 1;
}
int main()
{
	while(1)
	{
		memset(G,0,sizeof G);
		scanf("%d%d",&N,&M);
		if(!N&&!M)break;
		S=N+3;T=N+4;
		for(int i=1,a,b,w;i<=M;i++)
		{
			a=Read();
			b=Read();
			scanf("%d",&w);
			G[a][T]+=w;
			G[S][b]+=w;
			G[a][b]=INF;
		}
		G[N+2][N+1]=INF;
		n=T;
		int flow=sap();
		if(!check(flow))
			printf("impossible\n");
		else
			printf("%d\n",INF-G[N+2][N+1]);
	}
	return 0;
}
