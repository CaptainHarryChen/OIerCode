#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=1005;
int P[MAXN];
int main()
{
	int T,n;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		int ans=0;
		for(int i=1;i<=n;i++)
			scanf("%d",&P[i]);
		sort(P+1,P+n+1);
		if(n&1)
			for(int i=1;i<=n;i+=2)
				ans^=(P[i]-P[i-1]-1);
		else
			for(int i=2;i<=n;i+=2)
				ans^=(P[i]-P[i-1]-1);
		if(ans)
			puts("Georgia will win");
		else
			puts("Bob will win");
	}
	return 0;
}
