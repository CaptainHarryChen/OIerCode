#include<cstdio>
#include<cstring>
#include<cmath>
#include<map>
#include<algorithm>
using namespace std;
const long long MAXN=100005,MAXP=21000;

long long prime[MAXP],pcnt;
bool npr[MAXP];

void LinerSieve()
{
	npr[1]=true;
	for(long long i=2;i<MAXP;i++)
	{
		if(!npr[i])
			prime[++pcnt]=i;
		for(long long j=1;j<=pcnt&&prime[j]*i<MAXP;j++)
		{
			npr[prime[j]*i]=true;
			if(i%prime[j]==0)
				break;
		}
	}
}
long long ans;
map<long long,long long> cnt;
long long n,A[MAXN];
long long F(long long x)
{
	long long res=1;
	for(long long j=1;j<=pcnt&&prime[j]*prime[j]*prime[j]<=x;j++)
		if(x%prime[j]==0)
		{
			long long cnt=0;
			while(x%prime[j]==0)
				x/=prime[j],cnt++;
			cnt%=3;
			for(long long k=1;k<=cnt;k++)
				res*=prime[j];
		}
	if(x!=1)
		res*=x;
	return res;
}

int main()
{

	LinerSieve();
    scanf("%lld",&n);
    for(long long i=1;i<=n;i++)
        scanf("%lld",&A[i]);
	for(long long i=1;i<=n;i++)
	{
		A[i]=F(A[i]);
		cnt[A[i]]++;
		//printf("(%lld)\n",A[i]);
	}
	
	bool flag=false;
	for(long long i=1;i<=n;i++)
	{
		if(A[i]==1)
			flag=true;
		else if(cnt[A[i]])
		{
			long long tmp=floor(sqrt(A[i])+0.5);
			long long y;
			if(tmp*tmp==A[i])
				y=tmp;
			else
				y=A[i]*A[i];
			y=F(y);
			//printf("[%lld][%lld]\n",A[i],y);
			if(cnt.count(y))
			{
				//puts("1");
				ans+=max(cnt[y],cnt[A[i]]);
				cnt[y]=cnt[A[i]]=0;
			}
			else
			{
				ans+=cnt[A[i]];
				cnt[A[i]]=0;
			}
		}
	}
	if(flag)
		ans++;
	printf("%d\n",ans);

    fclose(stdin);
    fclose(stdout);
    return 0;
}