#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const long long MAXN=200005LL;

long long sq[MAXN],csq,nsq[MAXN],cnsq;

int main()
{
	long long n;
	scanf("%I64d",&n);
	for(long long i=1,a;i<=n;i++)
	{
		scanf("%I64d",&a);
		long long s=sqrt(a);
		if(s*s==a)
		{
			if(a==0)sq[++csq]=2;
			else sq[++csq]=1;
		}
		else
			nsq[++cnsq]=min(a-s*s,(s+1)*(s+1)-a);
	}
	sort(sq+1,sq+csq+1);
	sort(nsq+1,nsq+cnsq+1);
	long long res=0,i=1;
	while(csq>cnsq)
		res+=sq[i++],csq--,cnsq++;
	while(csq<cnsq)
		res+=nsq[i++],csq++,cnsq--;
	printf("%I64d\n",res);
	return 0;
}
