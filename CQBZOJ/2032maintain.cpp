#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#define MAXN 202
#define MAXW 6010
using namespace std;
int N,W,fa[MAXN];
struct edge
{
	int x,y,v;
	bool operator<(edge t)const
	{return v<t.v||(v==t.v&&(x<t.x||(x==t.x&&y<t.y)));}
}E[MAXW];
int root(int u)
{if(u==fa[u])return u;return fa[u]=root(fa[u]);}
int main()
{
	scanf("%d%d",&N,&W);
	for(int i=1;i<=W;i++)
	{
		edge t;
		scanf("%d%d%d",&t.x,&t.y,&t.v);
		int x;
		for(x=1;x<i;x++)
            if(E[x].v>t.v)
			{
                for(int k=i;k>x;k--)
                    E[k]=E[k-1];
                break;
            }
		E[x]=t;
		if(i<N-1)
		{printf("-1\n");continue;}
		for(int j=1;j<=N;j++)
			fa[j]=j;
		int ans=0,r1,r2;
		for(int j=1,k=0;j<N;j++)
		{
			for(k++;k<=i;k++)
			{
				r1=root(E[k].x),r2=root(E[k].y);
				if(r1!=r2)
				{
					fa[r1]=r2;
					ans+=E[k].v;
					break;
				}
			}
			if(k>i)
			{ans=-1;break;}
		}
		printf("%d\n",ans);
	}
	return 0;
}
