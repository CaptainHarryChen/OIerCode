#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=100005;

int N,L,Q;
int x[MAXN],nxt[MAXN][25];
int ans[MAXN];
//int dis[MAXN];

int main()
{
	scanf("%d",&N);
	for(int i=1;i<=N;i++)
		scanf("%d",&x[i]);
	scanf("%d%d",&L,&Q);
	memset(nxt,0x3F,sizeof nxt);
	for(int i=1;i<=N;i++)
	{
		nxt[i][0]=lower_bound(x+1,x+N+1,x[i]+L)-x;
		if(x[nxt[i][0]]>x[i]+L)
			nxt[i][0]--;
	}
	for(int j=1;(1<<j)<N;j++)
		for(int i=1;i<=N;i++)
			if(nxt[i][j-1]!=0x3F3F3F3F&&nxt[nxt[i][j-1]][j-1]!=0x3F3F3F3F)
				nxt[i][j]=nxt[nxt[i][j-1]][j-1];

	for(int i=1,a,b;i<=Q;i++)
	{
		scanf("%d%d",&a,&b);
		if(a>b)
			swap(a,b);
		int ans=0;
		for(int j=20;j>=0;j--)
			if(nxt[a][j]<=b)
			{
				a=nxt[a][j];
				ans+=(1<<j);
			}
		if(a<b)
			ans++;
		printf("%d\n",ans);
	}

	return 0;
}
