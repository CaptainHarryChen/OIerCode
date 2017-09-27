#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=205,MAXW=6005;
struct Edge
{
	int u,v,val;
};
Edge E[MAXW];
int fa[MAXN],id[MAXN],dep[MAXN];
bool vis[MAXN];
int LCA(int a,int b)
{
	memset(vis,0,sizeof vis);
	do
	{
		vis[a]=1;
		a=fa[a];
	}while(a!=-1);
	while(b!=-1&&!vis[b])
		b=fa[b];
	return b;
}
void Rev(int a,int son,int i)
{
	int b=fa[a],ii=id[a];
	fa[a]=son;
	id[a]=i;
	dep[a]=dep[son]+1;
	if(b==-1)
		return;
	Rev(b,a,ii);
}
int getmax(int u,int r)
{
	if(u==r)
		return 0;
	int t=getmax(fa[u],r);
	if(E[id[u]].val>E[id[t]].val)
		return u;
	return t;
}
int main()
{
	int N,W,lca,u,v,ans=0,cnt=0;
	scanf("%d%d",&N,&W);
	for(int i=1;i<=N;i++)
	{
		fa[i]=-1;
		dep[i]=1;
	}
	for(int i=1;i<=W;i++)
	{
		scanf("%d%d%d",&E[i].u,&E[i].v,&E[i].val);
		u=E[i].u,v=E[i].v;
		lca=LCA(u,v);
		if(lca==-1)
		{
			Rev(u,v,i);
			ans+=E[i].val;
			cnt++;
		}
		else
		{
			int a=getmax(u,lca);
			int b=getmax(v,lca);
			if(E[id[a]].val<=E[i].val&&E[id[b]].val<=E[i].val)
			{
				if(cnt==N-1)
					printf("%d\n",ans);
				else
					printf("-1\n");
				continue;
			}
			int c,d,e;
			if(E[id[a]].val>E[id[b]].val)
				c=u,d=v,e=a;
			else
				c=v,d=u,e=b;
			ans-=E[id[e]].val;
			ans+=E[i].val;
			fa[e]=-1;
			id[e]=0;
			Rev(c,d,i);
		}
		if(cnt==N-1)
			printf("%d\n",ans);
		else
			printf("-1\n");
	}
	return 0;
}
