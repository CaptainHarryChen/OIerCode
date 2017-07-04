#include<cstdio>
int mod_pow(int a,int b,int p)
{
	long long ret=1LL;
	while(b)
	{
		if(b&1)
			ret=1LL*(ret*a)%p;
		a=(1LL*a*a)%p;
		b>>=1;
	}
	return ret;
}
bool isprime(int x)
{
	for(int i=2;i*i<=x;i++)
		if(x%i==0)
			return 0;
	return 1;
}
int main()
{
	int p,a;
	while(1)
	{
		scanf("%d%d",&p,&a);
		if(!p&&!a)
			break;
		if(!isprime(p)&&mod_pow(a,p,p)==a)
			printf("yes\n");
		else
			printf("no\n");
	}
	return 0;
}
