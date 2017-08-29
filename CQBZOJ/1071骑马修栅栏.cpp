#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=505,MAXE=1100;
int E[MAXN][MAXN];
int ans[MAXE],cnt;
int deg[MAXN],n,m,S,T;
void euler(int id)
{
	for(int i=1;i<=n;i++)
		if(E[id][i]>0)
		{
			E[id][i]--;
			E[i][id]--;
			euler(i);
		}
	ans[++cnt]=id;
}
int main()
{
	int a,b;
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		E[a][b]++;
		E[b][a]++;
		deg[a]++;
		deg[b]++;
		n=max(n,a);
		n=max(n,b);
	}
	S=0;T=0;
	for(int i=1;i<=n;i++)
		if(deg[i]&1)
		{
			if(S)
			{
				T=i;
				break;
			}
			S=i;
		}
	if(S)
		euler(S);
	else
		euler(1);
	for(int i=cnt;i>=1;i--)
		printf("%d\n",ans[i]);
	return 0;
}
