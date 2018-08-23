#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=100005;

char str[3];
int n,A[MAXN],op[MAXN];
long long sum[MAXN],sum2[MAXN];

int main()
{
	scanf("%d",&n);
	op[1]=1;
	long long ans;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&A[i]);
		sum2[i]=sum2[i-1]+A[i];
		sum[i]=sum[i-1]+A[i]*op[i];
		if(i<n)
		{
			scanf("%s",str);
			op[i+1]=(str[0]=='+')?1:-1;
		}
	}
	
	int last=-1;
	op[n+1]=-1;
	ans=sum[n];
	for(int i=1;i<=n+1;i++)
		if(op[i]==-1)
		{
			if(last!=-1)
				ans=max(ans,sum2[n]-sum2[i-1]-(sum2[i-1]-sum2[last-1])+sum[last-1]);
			last=i;
		}
	printf("%lld\n",ans);
	
	return 0;
}
