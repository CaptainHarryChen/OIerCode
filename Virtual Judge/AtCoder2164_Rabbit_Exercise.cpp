#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=100005;

long long N,A[MAXN],M,K,ans[MAXN];
int P[MAXN],stk[MAXN],tp;
bool vis[MAXN];

int main()
{
	scanf("%lld",&N);
	for(int i=1;i<=N;i++)
	{
		scanf("%lld",&A[i]);
		P[i]=i;
	}
	scanf("%lld%lld",&M,&K);
	for(int i=N;i>=1;i--)
		A[i]=A[i]-A[i-1];
	for(int i=1;i<=M;i++)
	{
		int x;
		scanf("%d",&x);
		swap(P[x],P[x+1]);
	}
	for(int i=1;i<=N;i++)
		if(!vis[i])
		{
			int u=i;
			tp=0;
			while(!vis[u])
			{
				stk[++tp]=u;
				vis[u]=true;
				u=P[u];
			}
			for(int j=1;j<=tp;j++)
				ans[stk[j]]=A[stk[(K+j-1)%tp+1]];
		}
	for(int i=1;i<=N;i++)
		ans[i]+=ans[i-1];
	for(int i=1;i<=N;i++)
		printf("%lld.0\n",ans[i]);
	
	return 0;
}
