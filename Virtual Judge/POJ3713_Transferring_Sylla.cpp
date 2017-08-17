#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=505,MAXM=40005;
struct Edge
{
	int id;
	Edge *next;
	Edge(){}
	Edge(int i)
	{
		id=i;
	}
};
Edge E[MAXM],*ecur,*V[MAXN];
int dfn[MAXN],low[MAXN],dfcnt;
void add_edge(int a,int b)
{
	*ecur=Edge(b);
	ecur->next=V[a];
	V[a]=ecur;
	ecur++;
}
bool dfs(int id,int fa,int del)
{
	dfn[id]=dfcnt++;
	low[id]=dfn[id];
	int cnt=0;
	for(Edge *p=V[id];p;p=p->next)
	{
		if(p->id==del||p->id==fa)
			continue;
		if(dfn[p->id]==0)
		{
			cnt++;
			if(!dfs(p->id,id,del))
				return 0;
			low[id]=min(low[id],low[p->id]);
			if(fa==-1&&cnt>1)
				return 0;
			if(low[p->id]>=dfn[id]&&fa!=-1)
				return 0;
		}
		else
			low[id]=min(low[id],dfn[p->id]);
	}
	return 1;
}
int main()
{
	int N,M,a,b;
	bool flag;
	while(true)
	{
		scanf("%d%d",&N,&M);
		if(!N&&!M)
			break;
		memset(V,0,sizeof V);
		ecur=E;
		for(int i=1;i<=M;i++)
		{
			scanf("%d%d",&a,&b);
			add_edge(a,b);
			add_edge(b,a);
		}
		flag=1;
		for(int i=0;i<N&&flag;i++)
		{
			memset(dfn,0,sizeof dfn);
			memset(low,0x7F,sizeof low);
			dfcnt=1;
			dfn[i]=1;
			flag=dfs(i==0?1:0,-1,i);
			for(int j=0;j<N&&flag;j++)
				if(dfn[j]==0)
					flag=0;
		}
		if(flag)
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}
