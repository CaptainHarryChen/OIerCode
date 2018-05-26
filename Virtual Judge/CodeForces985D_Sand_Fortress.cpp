#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;

long long n,H;

int main()
{
	scanf("%I64d%I64d",&n,&H);
	long long L=1,R=n,tp=0,mid,sum;
	while(L<R)
	{
		mid=(L+R+1)/2LL,sum=0;
		if(mid>H)
		{
			if((double)(H+mid-1)/2.0*(mid-H)>1.0*n)
				sum=n+1;
			else
				sum=(H+mid-1)*(mid-H)/2LL;
		}
		if((double)(mid+1)*mid/2.0>n-sum)
			sum=n+1;
		else
			sum+=(mid+1)*mid/2LL;
		if(sum>n)
			R=mid-1;
		else
			L=mid;
	}
	tp=L;
	sum=0;
	if(tp>H)
		sum=(H+tp-1)*(tp-H)/2LL;
	sum+=(tp+1)*tp/2LL;
	
	long long ans=(tp>H?tp-H:0)+tp;
	ans+=(n-sum)/tp+((n-sum)%tp!=0);
	
	printf("%I64d\n",ans);
	
	return 0;
}
