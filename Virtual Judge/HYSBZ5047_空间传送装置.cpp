#include<cstdio>
#include<iostream>
#include<queue>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=100005,MAXE=200005,MAXM=55,MAXS=2005;
int dis[MAXN];
bool used[MAXN];
int n,m,s,e;
struct Edge
{
	int id,w;
	Edge *next;
	Edge(){}
	Edge(int a,int b){id=a;w=b;next=NULL;}
}E[MAXE],*V[MAXN],*cur=E;
queue<int>Q;
int mac[MAXM][4];
int dp[MAXM][MAXS];
void init()
{
	int temp;
	for(int i=1;i<=m;i++)
	{
		int a=mac[i][0],b=mac[i][1],c=mac[i][2],d=mac[i][3];
		temp=0;
		for(int j=0;j<c;j++)
			dp[i][0]=min(dp[i][0],(a*j+b)%c+d+j);
		dp[i][c]=dp[i][0];
		for(int s=c-1;s>0;s--)
		{
			dp[i][s]=dp[i][s+1]+1;
			dp[i][s]=min(dp[i][s],(a*s+b)%c+d);
		}
	}
}
void SPFA()
{
	memset(dis,0x3F,sizeof dis);
	dis[1]=s;
	used[1]=1;
	Q.push(1);
	while(!Q.empty())
	{
		int t=Q.front();
		Q.pop();used[t]=0;
		for(Edge *p=V[t];p;p=p->next)
		{
			int ndis=dp[p->w][dis[t]%mac[p->w][2]]+dis[t];
			if(dis[p->id]>ndis)
			{
				dis[p->id]=ndis;
				if(!used[p->id])
				{
					Q.push(p->id);
					used[p->id]=1;
				}
			}
		}
	}
}
int main()
{
	scanf("%d%d%d%d",&n,&m,&s,&e);
	for(int i=1;i<=m;i++)
		scanf("%d%d%d%d",mac[i],mac[i]+1,mac[i]+2,mac[i]+3);
	for(int i=1,u,v,w;i<=e;i++)
	{
		scanf("%d%d%d",&u,&v,&w);
		*cur=Edge(v,w);
		cur->next=V[u];
		V[u]=cur++;
	}
	memset(dp,0x3F,sizeof dp);
	init();
	SPFA();
	for(int i=2;i<=n;i++)
		if(dis[i]==0x3F3F3F3F)
			printf("-1\n");
		else
			printf("%d\n",dis[i]-s);
	return 0;
}
