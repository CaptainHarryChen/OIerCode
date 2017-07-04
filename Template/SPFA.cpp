#include<cstdio>
#include<iostream>
#include<queue>
#include<cstring>
using std::queue;
#define MAXN 505
int dis[MAXN],path[MAXN],print[MAXN];
int count[MAXN];
bool used[MAXN];
int n,m,s,t;
struct Edge
{
	int id,v;
	Edge*next;
	Edge(){id=v=0;next=NULL;}
	Edge(int a,int b){id=a;v=b;next=NULL;}
}edge[MAXN];
queue<int>Q;
bool SPFA()
{
	memset(dis,0x3F,sizeof dis);
	dis[s]=0;
	used[s]=1;
	Q.push(s);
	while(!Q.empty())
	{
		int t=Q.front();
		Q.pop();used[t]=0;
		for(Edge*p=edge[t].next;p;p=p->next)
			if(dis[p->id]>dis[t]+p->v)
			{
				dis[p->id]=dis[t]+p->v;
				path[p->id]=t;
				if(!used[p->id])
				{
					Q.push(p->id);
					used[p->id]=1;
					count[p->id]++;
					if(count[p->id]>n)
						return 0;
				}
			}
	}
	return 1;
}
int main()
{
	freopen("SPFA_data.in","r",stdin);
	scanf("%d%d",&n,&m);
	for(int i=1,a,b,c;i<=m;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		Edge*p=new Edge(b,c);
		p->next=edge[a].next;
		edge[a].next=p;
	}
	scanf("%d%d",&s,&t);
	if(!SPFA())
	{printf("No Solution\n");return 0;}
	printf("%d\n",dis[t]);
	int x=t,p=0;
	while(x!=s)
	{print[++p]=x;x=path[x];}
	printf("%d",s);
	for(int i=p;i>0;i--)
		printf(" %d",print[i]);
	printf("\n");
	return 0;
}
