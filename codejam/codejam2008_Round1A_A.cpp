#include<cstdio>
#include<algorithm>
using namespace std;
#define MAXN 805
int x[MAXN],y[MAXN];
bool cmp2(int x,int y){return x>y;}
int main()
{
	int T,n;
	scanf("%d",&T);
	for(int Case=1;Case<=T;Case++)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%d",x+i);
		for(int i=1;i<=n;i++)
			scanf("%d",y+i);
		sort(x+1,x+n+1);
		sort(y+1,y+n+1,cmp2);
		long long ans=0;
		for(int i=1;i<=n;i++)
			ans+=1LL*x[i]*y[i];
		printf("Case #%d: %I64d\n",Case,ans);
	}
	return 0;
}
