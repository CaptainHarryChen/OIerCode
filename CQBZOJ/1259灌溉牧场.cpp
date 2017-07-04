#include<cstdio>
#include<algorithm>
#define MAXN 305
#define MAXE 50010
int n,e,fa[MAXN],W[MAXN],ans;
struct edge{int x,y,v;}P[MAXE];
bool cmp(edge a,edge b){return a.v<b.v;}
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
	{
		scanf("%d",&W[i]);
		P[++e].x=0;
		P[e].y=i;
		P[e].v=W[i];
	}
	for(int i=1;i<=n;i++)
		for(int j=1,v;j<=n;j++)
		{
			scanf("%d",&v);
			if(j<i)
			{
				P[++e].x=i;
				P[e].y=j;
				P[e].v=v;
			}
		}
	std::sort(P+1,P+e+1,cmp);
	for(int i=1;i<=n;i++)fa[i]=i;
	int r1,r2;
	for(int i=1,u=1;i<=e&&u<=n;i++)
	{
		r1=root(P[i].x),r2=root(P[i].y);
        if(r1!=r2)
        {
            ans+=P[i].v;
			u++;
            fa[r1]=r2;
        }
	}
	printf("%d\n",ans);
	return 0;
}
