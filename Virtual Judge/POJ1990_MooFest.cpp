#include<cstdio>
#include<algorithm>
using namespace std;
const long long MAXN=20005;
typedef pair<long long,long long> cow;
class Tsum
{
	long long sum[MAXN];
public:
	void add(long long x,long long val)
	{
		for(;x<MAXN;x+=(x&(-x)))
			sum[x]+=val;
	}
	long long get(long long x)
	{
		long long ret=0;
		for(;x>0;x-=(x&(-x)))
			ret+=sum[x];
		return ret;
	}
};
long long N;
cow C[MAXN];
Tsum pos,cnt;
int main()
{
	scanf("%lld",&N);
	for(long long i=1;i<=N;i++)
		scanf("%lld%lld",&C[i].first,&C[i].second);
	sort(C+1,C+N+1);
	long long sum=0,ans=0;
	for(long long i=1;i<=N;i++)
	{
		long long x=C[i].second,v=C[i].first;
		ans+=v*(cnt.get(x)*x-pos.get(x)+sum-pos.get(x)-(i-cnt.get(x)-1)*x);
		cnt.add(C[i].second,1);
		pos.add(C[i].second,C[i].second);
		sum+=x;
	}
	printf("%lld\n",ans);
	return 0;
}
