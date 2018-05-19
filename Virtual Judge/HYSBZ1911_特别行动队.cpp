#include<cstdio>
const long long MAXN=1000005;

long long n,a,b,c;
long long x[MAXN],s[MAXN];
long long dp[MAXN],v[MAXN];
long long q[MAXN],h,t;

int main()
{
	scanf("%lld%lld%lld%lld",&n,&a,&b,&c);
	for(long long i=1;i<=n;i++)
	{
		scanf("%lld",x+i);
		s[i]=s[i-1]+x[i];
	}
	
	v[0]=0;
	q[1]=0;
	h=t=1;
	for(long long i=1;i<=n;i++)
	{
		while(t-h+1>=2&&v[q[h+1]]-v[q[h]]>2LL*a*s[i]*(s[q[h+1]]-s[q[h]]))
			h++;
		dp[i]=v[q[h]]-2LL*a*s[i]*s[q[h]]+b*s[i]+a*s[i]*s[i]+c;
		v[i]=dp[i]+a*s[i]*s[i]-b*s[i];
		while(t-h+1>=2&&(v[i]-v[q[t]])*(s[q[t]]-s[q[t-1]])>(v[q[t]]-v[q[t-1]])*(s[i]-s[q[t]]))
			t--;
		q[++t]=i;
	}
	
	printf("%lld\n",dp[n]);
	
	return 0;
}
