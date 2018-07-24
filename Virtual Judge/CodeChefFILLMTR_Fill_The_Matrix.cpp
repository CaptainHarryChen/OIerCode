#include<cstdio>
#include<cstring>
const int MAXN=100005;

int fa[MAXN],val[MAXN];
int Root(int x)
{
	if(fa[x]==0)
		return x;
	int f=Root(fa[x]);
	val[x]^=val[fa[x]];
	fa[x]=f;
	return f;
}
bool Union(int x,int y,int v)
{
	int r1=Root(x),r2=Root(y);
	if(r1==r2)
		return v==(val[x]^val[y]);
	fa[r1]=r2;
	val[r1]=(val[x]^val[y])^v;
	return true;
}

int main()
{
	int T,N,Q;
	scanf("%d",&T);
	while(T--)
	{
		memset(fa,0,sizeof fa);
		memset(val,0,sizeof val);
		scanf("%d%d",&N,&Q);
		bool flag=true;
		for(int i=1;i<=Q;i++)
		{
			int u,v,w;
			scanf("%d%d%d",&u,&v,&w);
			if(!Union(u,v,w))
				flag=false;
		}
		if(flag)
			puts("yes");
		else
			puts("no");
	}
	return 0;
}
