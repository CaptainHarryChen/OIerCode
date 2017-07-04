#include<cstdio>
#include<algorithm>
#define MAXN 110
#define MAXE MAXN*MAXN
int n,e,fa[MAXN],ans;
struct edge
{
	int x,y,v;
}E[MAXE];
bool cmp(edge a,edge b)
{
	return a.v<b.v;
}
void make_set(int n)
{
	for(int i=1;i<=n;i++)
		fa[i]=i;
}
int find(int u)
{
	if(fa[u]==u)
		return u;
	return fa[u]=find(fa[u]);
}
bool union_set(int u,int v)
{
	int x=find(u),y=find(v);
	if(x!=y)
	{fa[y]=x;return 1;}
	return 0;
}
int main()
{
	scanf("%d",&n);
	for(int i=1,x;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			scanf("%d",&x);
			if(i<j)
			{
				E[++e].x=i;
				E[e].y=j;
				E[e].v=x;
			}
		}
	std::sort(E+1,E+e+1,cmp);
	make_set(n);
	for(int i=1,j=1;i<=e&&j<n;i++)
		if(union_set(E[i].x,E[i].y))
		{ans+=E[i].v;j++;}
	printf("%d\n",ans);
	return 0;
}
