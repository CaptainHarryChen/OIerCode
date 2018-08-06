#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=100005;

bool vis[MAXN];
pair<int,int> lim[MAXN];
int A[MAXN];

int main()
{
	int T,n,m;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&m);
		for(int i=1;i<=m;i++)
			scanf("%d%d",&lim[i].first,&lim[i].second);
		sort(lim+1,lim+m+1);
		fill(vis+1,vis+n+1,0);
		int L=1,R=1,val=1;
		for(int i=1;i<=m;i++)
		{
			while(L<R&&L<lim[i].first)
			{
				val=min(val,A[L]);
				vis[A[L++]]=false;
			}
			while(L==R&&R<lim[i].first)
			{
				A[L]=1;
				L++;R++;
			}
			while(R<=lim[i].second)
			{
				A[R++]=val;
				vis[val]=true;
				while(vis[val])
					val++;
			}
		}
		for(int i=R;i<=n;i++)
			A[i]=1;
		for(int i=1;i<=n;i++)
			printf("%d%c",A[i],i==n?'\n':' ');
	}
	
	return 0;
}
