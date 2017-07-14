#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int MAXN=10000005;
int cnt[MAXN],prime[670000],pcnt;
long long po[MAXN],sum[MAXN];
bool nprime[MAXN];
void Init()
{
	nprime[1]=1;
	cnt[1]=0;
	for(int i=2;i<MAXN;i++)
	{
		if(!nprime[i])
		{
			prime[++pcnt]=i;
			cnt[i]=1;
			po[i]=i;
			sum[i]=1;
		}
		for(int j=1;j<=pcnt&&i*prime[j]<MAXN;j++)
		{
			nprime[i*prime[j]]=1;
			if(i%prime[j]==0)
			{
				cnt[i*prime[j]]=cnt[i]+1;
				po[i*prime[j]]=po[i]*prime[j];
				int temp=i*prime[j]/po[i*prime[j]];
				if(temp==1)
					sum[i*prime[j]]=1;
				else if(cnt[temp]==cnt[i*prime[j]])
					sum[i*prime[j]]=-sum[temp];
				break;
			}
			po[i*prime[j]]=prime[j];
			cnt[i*prime[j]]=1;
			if(cnt[i*prime[j]]==cnt[i])
				sum[i*prime[j]]=-sum[i];
		}
	}
	for(int i=1;i<MAXN;i++)
		sum[i]+=sum[i-1];
}
int main()
{
	Init();
	int n,a,b;
	scanf("%d",&n);
	while(n--)
	{
		scanf("%d%d",&a,&b);
		long long ans=0;
		if(a>b)
			swap(a,b);
		int last;
		for(int i=1;i<=a;i=last+1)
		{
			last=min(a/(a/i),b/(b/i));
			ans+=1LL*(sum[last]-sum[i-1])*(a/i)*(b/i);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
