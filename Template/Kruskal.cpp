#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=105,MAXE=MAXN*MAXN;

struct Edge
{
	int u,v,len;
	Edge(){}
	Edge(int _u,int _v,int _len)
	{u=_u;v=_v;len=_len;}
	bool operator < (const Edge &t)const
	{return len<t.len;}
};

int dsu[MAXN];
int Root(int x)
{
	if(dsu[x]==0)
		return x;
	return (dsu[x]=Root(dsu[x]));
}

int n,m;
Edge edge[MAXE];

int Kruskal()
{
	sort(edge+1,edge+m+1);
	int ans=0;
	for(int i=1;i<=m;i++)
	{
		int r1=Root(edge[i].u),r2=Root(edge[i].v);
		if(r1==r2)
			continue;
		dsu[r1]=r2;
		ans+=edge[i].len;
	}
	return ans;
}

int main()
{
	freopen("Kruskal_data.in","r",stdin);
	scanf("%d%d",&n,&m);
	for(int i=1,a,b,c;i<=m;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		edge[i]=Edge(a,b,c);
	}
	
	printf("%d\n",Kruskal());
	
	return 0;
}
