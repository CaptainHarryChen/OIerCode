#include<cstdio>
#include<queue>
#include<cstring>
using std::queue;
using std::min;
#define MAXN 210
#define INF 0x7FFFFFFF
int n,k,S,T;
char str[MAXN/4][MAXN/4];
int G[MAXN][MAXN],G2[MAXN][MAXN];
int d[MAXN],cntd[MAXN];
void bfs()
{
	memset(d,0x3F,sizeof d);
	memset(cntd,0,sizeof cntd);
	queue<int>Q;
	d[T]=0;
	cntd[0]=1;
	Q.push(T);
	while(!Q.empty())
	{
		int t=Q.front();Q.pop();
		for(int i=0;i<=n;i++)
			if(G[i][t]&&i!=T&&d[i]>d[t]+1)
			{
				d[i]=d[t]+1;
				cntd[d[i]]++;
				Q.push(i);
			}
	}
}
int aug(int now,int augco)
{
	int augc=augco,mn=n-1;
	if(now==T)
		return augco;
	for(int i=0,temp;i<=n;i++)
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
	int flow=0;
	while(d[S]<n)
		flow+=aug(S,INF);
	return flow;
}
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
		scanf("%s",str[i]+1);
	S=0,T=4*n+1;
	for(int i=1;i<=n;i++)
	{
		//G2[S][i]=INF;
		G2[i][i+n]=k;
		//G2[i+n*2][T]=INF;
		G2[i+n*3][i+n*2]=k;
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(str[i][j]=='Y')
				G2[i][j+n*2]=1;
			else
				G2[i+n][j+n*3]=1;
	for(int temp=1;;temp++)
	{
		memcpy(G,G2,sizeof G);
		for(int i=1;i<=n;i++)
			G[S][i]=temp,G[i+n*2][T]=temp;
		n=n*4+1;
		bfs();
		if(temp*((n-1)/4)>sap())
		{printf("%d\n",temp-1);break;}
		n=(n-1)/4;
	}
	return 0;
}
