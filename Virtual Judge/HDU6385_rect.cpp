#include<cstdio>
#include<algorithm>
using namespace std;

int main()
{
	int T,MX,MY,N;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d",&MX,&MY,&N);
		long long ans=0;
		for(int i=1;i<=N;i++)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			ans+=min(min(x,MX-x),min(y,MY-y));
		}
		printf("%I64d\n",ans);
	}
	
	return 0;
}
