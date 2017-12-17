#include<cstdio>
int main()
{
	long long n,a,b;
	scanf("%I64d%I64d%I64d",&n,&a,&b);
	for(long long i=0;i*a<=n;i++)
		if((n-i*a)%b==0)
		{
			printf("YES\n%I64d %I64d\n",i,(n-i*a)/b);
			return 0;
		}
	puts("NO");
	return 0;
}
