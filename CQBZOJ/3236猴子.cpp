#include<cstdio>
#include<iostream>
using namespace std;
#define MAXN 200005
int n,m,hand[MAXN][3];
int input[MAXN*2][2];
int set[MAXN],NEXT[MAXN],last[MAXN];
int ans[MAXN];
bool flag[MAXN][3];
int Find(int x)
{return set[x]==x?x:set[x]=Find(set[x]);}
void Union(int t,int x,int y)
{
	if(Find(x)==1)swap(x,y);
	int fx=Find(x),fy=Find(y);
	if(fx==fy)return;
	if(fy==1)
		for(int i=fx;i;i=NEXT[i])
			ans[i]=t;
	set[fx]=fy;
	NEXT[last[fy]]=fx;
	last[fy]=last[fx];
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&hand[i][1],&hand[i][2]);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&input[i][0],&input[i][1]);
		flag[input[i][0]][input[i][1]]=1;
	}
	for(int i=1;i<=n;i++)
		set[i]=last[i]=i;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=2;j++)
			if(!flag[i][j]&&hand[i][j]!=-1)
				Union(-1,i,hand[i][j]);
	for(int i=m;i>0;i--)
		Union(i-1,input[i][0],hand[input[i][0]][input[i][1]]);
	printf("-1\n");
	for(int i=2;i<=n;i++)
		printf("%d\n",ans[i]);
	return 0;
}
