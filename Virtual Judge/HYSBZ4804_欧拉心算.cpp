#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int MAXN=10000005;
int mu[MAXN],prime[670000],pcnt,fai[MAXN];
long long sum[MAXN],po[MAXN];
bool nprime[MAXN];
void Init()
{
	nprime[1]=1;mu[1]=1;fai[1]=1;
	sum[1]=1;
	for(int i=2;i<MAXN;i++)
	{
		if(!nprime[i])
		{
			prime[++pcnt]=i;
			mu[i]=-1;
			fai[i]=i-1;
			po[i]=i;
			sum[i]=fai[1]*mu[i]+fai[i]*mu[1];
		}
		for(int j=1;j<=pcnt&&i*prime[j]<MAXN;j++)
		{
			nprime[i*prime[j]]=1;
			if(i%prime[j]==0)
			{
				po[i*prime[j]]=po[i]*prime[j];
				fai[i*prime[j]]=fai[i]*prime[j];
				int temp=i*prime[j]/po[i*prime[j]];
				if(temp==1)
					sum[i*prime[j]]=fai[i*prime[j]]-fai[i];
				else
					sum[i*prime[j]]=sum[po[i*prime[j]]]*sum[temp];
				break;
			}
			po[i*prime[j]]=prime[j];
			fai[i*prime[j]]=(prime[j]-1)*fai[i];
			sum[i*prime[j]]=sum[i]*sum[prime[j]];
			mu[i*prime[j]]=-mu[i];
		}
	}
	for(int i=1;i<MAXN;i++)
		sum[i]+=sum[i-1];
}
int main()
{
	Init();
	long long ans;
	int n,last,T;
	scanf("%d",&T);
	while(T--)
	{
		ans=0;
		scanf("%d",&n);
		for(int d=1;d<=n;d=last+1)
		{
			last=n/(n/d);
			ans+=1LL*(sum[last]-sum[d-1])*(n/d)*(n/d);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
