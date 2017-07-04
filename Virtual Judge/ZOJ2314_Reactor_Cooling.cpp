#include<cstdio>
#include<cstring>
#include<queue>
using std::queue;
using std::min;
#define MAXN 210
int n,m,S,T;
int G[MAXN][MAXN];
int d[MAXN],cntd[MAXN];
int edge[MAXN*MAXN][4];
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
	int task;
	scanf("%d",&task);
	while(task--)
	{
		memset(G,0,sizeof G);
		scanf("%d%d",&n,&m);
		T=n+1;S=n+2;
		for(int i=1,a,b,x,y;i<=m;i++)
		{
			scanf("%d%d%d%d",&a,&b,&x,&y);
			edge[i][0]=a;
			edge[i][1]=b;
			edge[i][2]=x;
			edge[i][3]=y;
			G[a][T]+=x;
			G[S][b]+=x;
			G[a][b]+=y-x;
		}
		n=n+2;
		bfs();
		int flow=sap();
		n=n-2;
		if(!check(flow))
			printf("NO\n\n");
		else
		{
			printf("YES\n");
			for(int i=1;i<=m;i++)
				printf("%d\n",edge[i][3]-G[edge[i][0]][edge[i][1]]);
			printf("\n");
		}
	}
	return 0;
}
