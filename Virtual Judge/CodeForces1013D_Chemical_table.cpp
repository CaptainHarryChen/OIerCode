#include<cstdio>
const int MAXN=200005;

int n,m,q,ans;

int fa[MAXN*2];
int Root(int x)
{
	if(fa[x]==0)
		return x;
	return fa[x]=Root(fa[x]);
}
void Union(int x,int y)
{
	int r1=Root(x),r2=Root(y);
	if(r1==r2)
		return;
	fa[r1]=r2;
}

int main()
{
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=q;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		Union(x,y+n);
	}
	int cnt=0;
	for(int i=1;i<=n+m;i++)
		cnt+=(fa[i]==0);
	printf("%d\n",cnt-1);
	
	return 0;
}
