#include<cstdio>
#include<algorithm>
using std::sort;
#define MAXN 110
#define MAXE MAXN*MAXN
int n,m,S[MAXN],ans;
struct Edge
{
	int x,y,v;
	bool operator<(Edge t)const
	{return v<t.v;}
}edge[MAXE];
int Find(int x)
{return S[x]==x?x:S[x]=Find(S[x]);}
void Kruskal()
{
	for(int i=1;i<=m;i++)
	{
		int r1=Find(edge[i].x),r2=Find(edge[i].y);
		if(r1==r2)continue;
		S[r1]=r2;
		ans+=edge[i].v;
	}
}
int main()
{
	freopen("Kruskal_data.in","r",stdin);
	scanf("%d",&n);
	for(int i=1,x;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			scanf("%d",&x);
			if(i<j)
			{
				edge[++m].x=i;
				edge[m].y=j;
				edge[m].v=x;
			}
		}
	sort(edge+1,edge+m+1);
	for(int i=1;i<=n;i++)
		S[i]=i;
	Kruskal();
	printf("%d\n",ans);
	return 0;
}
