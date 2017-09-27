#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=1005,MAXM=100005;
struct Edge
{
	int u,v,id;
	bool ty;
	Edge(){}
	Edge(int _u,int _v,bool t,int i):u(_u),v(_v),id(i){ty=t;}
	bool operator < (const Edge &t)const
	{return ty<t.ty;}
};
Edge E[MAXM];
int ecnt;
struct Tree
{
	int fa[MAXN],id[MAXN];
	bool vis[MAXN];
	int LCA(int a,int b)
	{
		memset(vis,0,sizeof vis);
		while(a)
		{
			vis[a]=true;
			a=fa[a];
		}
		while(b)
		{
			if(vis[b])
				return b;
			b=fa[b];
		}
		return -1;
	}
	void Rev(int u,int son,int i)
	{
		int v=fa[u],ii=id[u];
		fa[u]=son;
		id[u]=i;
		if(v)
			Rev(v,u,ii);
	}
	int FindM(int u,int lca)
	{
		if(u==lca)
			return 0;
		if(E[id[u]].ty==true)
			return u;
		return FindM(fa[u],lca);
	}
};
Tree S;
bool used[MAXM];
int main()
{
	int n,m,c1=0,c2=0;
	scanf("%d%d",&n,&m);
	if(n%2==0)
	{
		printf("-1\n");
		return 0;
	}
	int ii=0;
	for(int i=1,u,v;i<=m;i++)
	{
		char ty[5];
		scanf("%d%d%s",&u,&v,ty);
		ii++;
		if(u==v)
		{
			m--,i--;
			continue;
		}
		if(ty[0]=='S')
		{
			E[++ecnt]=Edge(u,v,0,ii);
			c1++;
		}
		else
		{
			E[++ecnt]=Edge(u,v,1,ii);
			c2++;
		}
	}
	if(c1<(n-1)/2||c2<(n-1)/2)
	{
		printf("-1\n");
		return 0;
	}
	sort(E+1,E+ecnt+1);
	int cnt=0,cnt2=0,i1=1,i2=c1+1,lca;
	for(int i=i2;i<=m;i++)
	{
		lca=S.LCA(E[i].u,E[i].v);
		if(lca==-1)
		{
			S.Rev(E[i].u,E[i].v,i);
			used[i]=1;
			cnt++;
			cnt2++;
		}
	}
	for(int i=i1;i<=m;i++)
	{
		lca=S.LCA(E[i].u,E[i].v);
		if(lca==-1)
		{
			S.Rev(E[i].u,E[i].v,i);
			used[i]=1;
			cnt--;
			cnt2++;
		}
	}
	if(cnt2!=n-1)
	{
		printf("-1\n");
		return 0;
	}
	for(int i=i1;i<=c1&&cnt;i++)
		if(!used[i])
		{
			lca=S.LCA(E[i].u,E[i].v);
			int a=S.FindM(E[i].u,lca);
			int b=S.FindM(E[i].v,lca);
			if(!a&&!b)
				continue;
			int c,d,e;
			if(a)
				c=E[i].u,d=E[i].v,e=a;
			else
				c=E[i].v,d=E[i].u,e=b;
			used[S.id[e]]=0;
			used[i]=1;
			S.fa[e]=0;
			S.id[e]=0;
			cnt-=2;
			S.Rev(c,d,e);
		}
	if(cnt)
	{
		printf("-1\n");
		return 0;
	}
	int pcnt=0;
	for(int i=1;i<=m;i++)
		pcnt+=used[i];
	printf("%d\n",pcnt);
	for(int i=1;i<=m;i++)
		if(used[i])
			printf("%d ",E[i].id);
	return 0;
}
