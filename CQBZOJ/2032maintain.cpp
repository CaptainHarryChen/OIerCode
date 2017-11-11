#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=205,MAXM=6005;

struct Edge
{
	int u,v,w;
	Edge(){}
	Edge(int _u,int _v,int _w)
	{u=_u;v=_v;w=_w;}
};
Edge E[MAXM];
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
		while(b&&vis[b]==false)
			b=fa[b];
		return b;
	}
	int Max(int u,int ed)
	{
		int mx=-1,res=0;
		while(u&&u!=ed)
		{
			if(mx<E[id[u]].w)
			{
				mx=E[id[u]].w;
				res=u;
			}
			u=fa[u];
		}
		return res;
	}
	void Rev(int u,int v,int i)
	{
		int f,fi;
		while(u)
		{
			f=fa[u];
			fi=id[u];
			fa[u]=v;
			id[u]=i;
			v=u;
			u=f;
			i=fi;
		}
	}
};

Tree T;
int main()
{
	int n,m,u,v,w,cnt=0,ans=0;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&u,&v,&w);
		E[i]=Edge(u,v,w);
		int l=T.LCA(u,v);
		if(l)
		{
			int a=T.Max(u,l),b=T.Max(v,l);
			int ai=T.id[a],bi=T.id[b];
			if(E[ai].w<E[bi].w)
			{
				swap(ai,bi);
				swap(a,b);
				swap(u,v);
			}
			if(E[ai].w>w)
			{
				T.fa[a]=T.id[a]=0;
				T.Rev(u,v,i);
				ans=ans-E[ai].w+w;
			}
		}
		else
		{
			T.Rev(u,v,i);
			cnt++;
			ans+=w;
		}
		if(cnt<n-1)
			puts("-1");
		else
			printf("%d\n",ans);
	}
	return 0;
}
