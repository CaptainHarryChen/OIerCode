#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
const int MAXN=205;
int E[MAXN][MAXN];
int lev[MAXN];
int iter[MAXN];
void update(int S,int T,int n)
{
	queue<int>Q;
	memset(lev,0x7F,sizeof lev);
	Q.push(S);
	lev[S]=0;
	while(!Q.empty())
	{
		int t=Q.front();
		Q.pop();
		for(int i=1;i<=n;i++)
			if(lev[i]>=n&&E[t][i]>0)
			{
				lev[i]=lev[t]+1;
				Q.push(i);
			}
	}
}
int aug(int u,int augco,int T,int n)
{
	if(u==T)
		return augco;
	int delta;
	for(int &i=iter[u];i<=n;i++)
		if(E[u][i]>0&&lev[i]==lev[u]+1)
		{
			delta=aug(i,min(augco,E[u][i]),T,n);
			if(delta>0)
			{
				E[u][i]-=delta;
				E[i][u]+=delta;
				return delta;
			}
		}
	return 0;
}
int Dinic(int S,int T,int n)
{
	int flow=0,temp;
	while(update(S,T,n),lev[T]<n)
	{
		memset(iter,0,sizeof iter);
		while(temp=aug(S,0x7FFFFFFF,T,n),temp)
			flow+=temp;
	}
	return flow;
}
int main()
{
	freopen("Dinic_matrix_data.in","r",stdin);
	int N,M,a,b,c;
	scanf("%d%d",&M,&N);
	for(int i=1;i<=M;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		E[a][b]+=c;
	}
	printf("%d\n",Dinic(1,N,N));
	return 0;
}
