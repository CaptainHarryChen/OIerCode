#include<cstdio>
#include<algorithm>
using namespace std;
#define MAXN 1005
#define MAXM 20005
int N,M;
struct edge
{
	int x,y,l;
	edge(){}
	edge(int _x,int _y,int _l){x=_x;y=_y;l=_l;}
	bool operator < (const edge &t)const
	{return l>t.l;}
}E[MAXM];
int Set[MAXN];
int Root(int x){return Set[x]==x?x:Set[x]=Root(Set[x]);}
int main()
{
	scanf("%d%d",&N,&M);
	for(int i=1;i<=N;i++)
		Set[i]=i;
	for(int i=1;i<=M;i++)
		scanf("%d%d%d",&E[i].x,&E[i].y,&E[i].l);
	sort(E+1,E+M+1);
	int last=0,ans=0;
	for(int i=1;i<N;i++)
	{
		bool suc=0;
		for(int j=last+1;j<=M;j++)
		{
			int r1=Root(E[j].x),r2=Root(E[j].y);
			if(r1!=r2)
			{
				ans+=E[j].l;
				Set[r1]=r2;
				last=j;
				suc=1;
				break;
			}
		}
		if(!suc)
		{
			printf("-1\n");
			return 0;
		}
	}
	printf("%d\n",ans);
	return 0;
}
