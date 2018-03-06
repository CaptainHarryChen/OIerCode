#include<cstdio>
#include<algorithm>
using namespace std;

int n,k,A,B;
long long ans;

int main()
{
	scanf("%d%d%d%d",&n,&k,&A,&B);
	if(k==1)
	{
		printf("%I64d\n",1LL*A*(n-1));
		return 0;
	}
	while(n>1)
	{
		if(n%k==0)
		{
			if(1LL*A*(n-n/k)>B)
				ans+=1LL*B;
			else
				ans+=1LL*A*(n-n/k);
			n/=k;
		}
		else
		{
			if(n<k)
			{
				ans+=1LL*A*(n-1);
				break;
			}
			ans+=1LL*A*(n%k);
			n-=n%k;
		}
	}
	printf("%I64d\n",ans);
	return 0;
}
