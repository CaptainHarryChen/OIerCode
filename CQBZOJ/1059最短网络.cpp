#include<cstdio>
#include<algorithm>
#define MAXE 5050
#define MAXN 105
int n,e,fa[MAXN];
struct edge{int x,y,v;}E[MAXE];
bool cmp(edge a,edge b)
{return a.v<b.v;}
int root(int u)
{
	if(fa[u]==u)
		return u;
	return fa[u]=root(fa[u]);
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=1,x;j<=n;j++)
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
	for(int i=1;i<=n;i++)fa[i]=i;
	int r1,r2,ans=0;
	for(int k=1,j=1;k<=e&&j<n;k++)
	{
		r1=root(E[k].x),r2=root(E[k].y);
		if(r1!=r2)
		{
			ans+=E[k].v;
			j++;
			fa[r1]=r2;
		}
	}
	printf("%d\n",ans);
	return 0;
}
