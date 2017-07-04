#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
#define MAXN 20005
#define MAXM 100005
struct Hate
{
	int x,y,v;
	bool operator < (Hate t)const
	{return v>t.v;}
}hate[MAXM];
int n,m;
int fa[MAXN*2];
int root(int x)
{return fa[x]==x?x:fa[x]=root(fa[x]);}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
		scanf("%d%d%d",&hate[i].x,&hate[i].y,&hate[i].v);
	sort(hate+1,hate+m+1);
	int ans=0;
	for(int i=1;i<=n*2;i++)
		fa[i]=i;
	for(int i=1;i<=m;i++)
	{
		int x=root(hate[i].x),y=root(hate[i].y);
		if(x==y)
		{
			ans=hate[i].v;
			break;
		}
		fa[x]=root(hate[i].y+n);
		fa[y]=root(hate[i].x+n);
	}
	printf("%d\n",ans);
	return 0;
}
