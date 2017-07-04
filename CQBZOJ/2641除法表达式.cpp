#include<cstdio>
#include<cstdlib>
#define MAXN 10010
long long N,num[MAXN];
int gcd(long long a,long long b)
{
	if(b==0)return a;
	return gcd(b,a%b);
}
int main()
{
	scanf("%lld",&N);
	if(N==1||N==0)
	{printf("YES\n");return 0;}
	for(int i=1;i<=N;i++)
		scanf("%lld",&num[i]);
	bool flag=0;
	for(long long i=3,s2=num[2]/(num[2]>num[1]?gcd(num[2],num[1]):gcd(num[1],num[2]));i<=N;i++)
	{
		s2/=(s2>num[i]?gcd(s2,num[i]):gcd(num[i],s2));
		if(s2==1)
		{flag=1;break;}
	}
	if(flag)
	{printf("YES\n");return 0;}
	printf("NO\n");return 0;
}
