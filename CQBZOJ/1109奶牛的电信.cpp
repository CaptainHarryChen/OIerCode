#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using std::queue;
using std::min;
using std::sort;
#define MAXN 105
#define INF 0x7FFFFFFF
int n,m,c1,c2,S,T;
int G[MAXN*2][MAXN*2],G2[MAXN*2][MAXN*2];
int d[MAXN*2],cntd[MAXN*2];
int print[MAXN],tot;
bool flag[MAXN];
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
		for(int i=1;i<=n;i++)
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
	int flow=0;
	while(d[S]<n)
		flow+=aug(S,INF);
	return flow;
}
int main()
{
	scanf("%d%d%d%d",&n,&m,&c1,&c2);
	for(int i=1;i<=n;i++)
	{
		G2[i*2-1][i*2]=1;
		if(i==c1||i==c2)
			G2[i*2-1][i*2]=INF;
	}
	for(int i=1,a,b;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		G2[a*2][b*2-1]=INF;
		G2[b*2][a*2-1]=INF;
	}
	memcpy(G,G2,sizeof G);
	n=n*2;
	S=c1*2;
	T=c2*2-1;
	bfs();
	int flow=sap();
	printf("%d\n",flow);
	for(int i=1,temp;i<=n/2;i++)
	{
		if(i==c1||i==c2)continue;
		memcpy(G,G2,sizeof G);
		flag[i]=1;
		for(int j=1;j<=n;j++)
			if(flag[j])
				G[j*2-1][j*2]=0;
		bfs();
		temp=sap();
		if(temp<flow)
		{print[++tot]=i;flow=temp;}
		else flag[i]=0;
		if(flow==0)break;
	}
	sort(print+1,print+tot+1);
	for(int i=1;i<tot;i++)
		printf("%d ",print[i]);
	printf("%d\n",print[tot]);
	return 0;
}
