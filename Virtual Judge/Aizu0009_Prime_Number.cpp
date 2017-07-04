#include<cstdio>
#include<algorithm>
using namespace std;
int prime[1000005],cur;
bool isprime[1000005];
int main()
{
	isprime[1]=1;
	for(int i=2;i<1000000;i++)
		if(!isprime[i])
		{
			prime[cur++]=i;
			for(long long j=1LL*i*i;j<1000000LL;j+=1LL*i)
				isprime[j]=1;
		}
	int n;
	while(~scanf("%d",&n))
		printf("%d\n",lower_bound(prime,prime+cur,n)-prime+(!isprime[n]));
	return 0;
}
