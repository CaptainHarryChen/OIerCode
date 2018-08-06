#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=200005;

int n,m;

int main()
{
	scanf("%d%d",&n,&m);
	long long sum=0,ans=0;
	for(int i=1;i<=n;i++)
	{
		int a;
		scanf("%d",&a);
		long long tmp=sum+(m-sum%m);
		ans=0;
		if(tmp<=sum+a)
			ans=(sum+a-tmp)/m+1;
		sum+=a;
		printf("%I64d ",ans);
	}
	puts("");
	
	return 0;
}
