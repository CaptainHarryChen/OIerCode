#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=1005,MAXM=100005;

struct Edge
{
	int u,v,id;
	Edge(){}
	Edge(int u,int v,int id):u(u),v(v),id(id){}
};

struct DSU
{
	int dsu[MAXN];
	int Root(int x)
	{
		if(dsu[x]==0)
			return x;
		return dsu[x]=Root(dsu[x]);
	}
}D1,D2;

int n,m;
bool use[MAXM];
Edge S[MAXM],M[MAXM];
int sc,mc;

int main()
{
	scanf("%d%d",&n,&m);
	if(n%2==0)
	{puts("-1");return 0;}
	for(int i=1;i<=m;i++)
	{
		int u,v;
		char ch[4];
		scanf("%d%d%s",&u,&v,ch);
		if(ch[0]=='S')
			S[++sc]=Edge(u,v,i);
		else
			M[++mc]=Edge(u,v,i);
	}
	int cnt=0;
	for(int i=1;i<=sc;i++)
	{
		int r1=D1.Root(S[i].u),r2=D1.Root(S[i].v);
		if(r1==r2)
			continue;
		D1.dsu[r1]=r2;
		//use[S[i].id]=true;
		cnt++;
	}
	if(cnt<(n-1)/2)
	{puts("-1");return 0;}
	int cnt2=0;
	for(int i=1;i<=mc;i++)
	{
		int r1=D1.Root(M[i].u),r2=D1.Root(M[i].v);
		if(r1==r2)
			continue;
		D1.dsu[r1]=r2;
		r1=D2.Root(M[i].u),r2=D2.Root(M[i].v);
		D2.dsu[r1]=r2;
		use[M[i].id]=true;
		cnt2++;
	}
	if(cnt+cnt2!=n-1)
	{puts("-1");return 0;}
	for(int i=1;i<=mc&&cnt2<(n-1)/2;i++)
	{
		int r1=D2.Root(M[i].u),r2=D2.Root(M[i].v);
		if(r1==r2)
			continue;
		D2.dsu[r1]=r2;
		use[M[i].id]=true;
		cnt2++;
	}
	if(cnt2<(n-1)/2)
	{puts("-1");return 0;}
	for(int i=1;i<=sc;i++)
	{
		int r1=D2.Root(S[i].u),r2=D2.Root(S[i].v);
		if(r1==r2)
			continue;
		D2.dsu[r1]=r2;
		use[S[i].id]=true;
		cnt2++;
	}
	if(cnt2!=n-1)
	{puts("-1");return 0;}
	printf("%d\n",n-1);
	for(int i=1;i<=m;i++)
		if(use[i])
			printf("%d ",i);
	
	return 0;
}
