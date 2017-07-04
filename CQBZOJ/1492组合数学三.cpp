#include<cstdio>
#include<cmath>
long long n,a,b,num[20],ans;
long long gcd(long long a,long long b)
{
	if(b==0)return a;
	return gcd(b,a%b);
}
long long count(long long k,long long a,long long b)
{
	long long t=a%k,s=1+(t==0);
	a=a+k-t;
	if(a>b)return 0;
	s+=(b-a)/k;
	return s;
}
void dfs(int k,long long s,int id)
{
	int flag=k%2==1?-1:1;
	ans+=count(s,a,b)*flag;
	if(k==n)return;
	for(int i=id+1;i<=n;i++)
			dfs(k+1,s*num[i]/(s>num[i]?gcd(s,num[i]):gcd(num[i],s)),i);
}
int main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld",&num[i]);
	scanf("%lld%lld",&a,&b);
	ans=count(8,a,b);
	for(int i=1;i<=n;i++)
		dfs(1,8*num[i]/(8>num[i]?gcd(8,num[i]):gcd(num[i],8)),i);
	printf("%lld\n",ans);
}
