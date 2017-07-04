#include<cstdio>
#include<algorithm>
using namespace std;
#define MAXN 105
#define MAXM MAXN*MAXN
int N;
struct edge
{
	int x,y,l;
	edge(){}
	edge(int _x,int _y,int _l){x=_x;y=_y;l=_l;}
	bool operator < (const edge &t)const
	{return l<t.l;}
}E[MAXM];
int Set[MAXN];
int Root(int x){return Set[x]==x?x:Set[x]=Root(Set[x]);}
int main()
{
	while(~scanf("%d",&N))
	{
		int cur=0;
		for(int i=1;i<=N;i++)
			Set[i]=i;
		for(int i=1,x;i<=N;i++)
			for(int j=1;j<=N;j++)
			{
				scanf("%d",&x);
				if(i!=j)
					E[++cur]=edge(i,j,x);
			}
		sort(E+1,E+cur+1);
		int last=0,ans=0;
		for(int i=1;i<N;i++)
			for(int j=last+1;j<=cur;j++)
			{
				int r1=Root(E[j].x),r2=Root(E[j].y);
				if(r1!=r2)
				{
					ans+=E[j].l;
					Set[r1]=r2;
					last=j;
					break;
				}
			}
		printf("%d\n",ans);
	}
	return 0;
}
