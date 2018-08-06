#include<cstdio>
#include<map>
using namespace std;
const int MAXN=200005;

struct DSU
{
	int fa[MAXN];
	int Root(int x)
	{return fa[x]==0?x:fa[x]=Root(fa[x]);}
	void Union(int x,int y)
	{
		int r1=Root(x),r2=Root(y);
		if(r1==r2)
			return;
		fa[r1]=r2;
	}
};

DSU s1,s2;
map<int,int> cnt[MAXN];

int main()
{
	int N,K,L;
	scanf("%d%d%d",&N,&K,&L);
	for(int i=1,x,y;i<=K;i++)
	{
		scanf("%d%d",&x,&y);
		s1.Union(x,y);
	}
	for(int i=1,x,y;i<=L;i++)
	{
		scanf("%d%d",&x,&y);
		s2.Union(x,y);
	}
	for(int i=1;i<=N;i++)
		cnt[s1.Root(i)][s2.Root(i)]++;
	for(int i=1;i<=N;i++)
		printf("%d ",cnt[s1.Root(i)][s2.Root(i)]);
	puts("");
	
	return 0;
}
