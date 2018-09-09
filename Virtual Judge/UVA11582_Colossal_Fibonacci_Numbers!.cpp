#include<cstdio>
const int MAXN=1005;

unsigned long long PowMod(unsigned long long a,unsigned long long b,unsigned long long p)
{
	unsigned long long res=1;
	while(b)
	{
		if(b&1)
			res=res*a%p;
		b>>=1;
		a=a*a%p;
	}
	return res;
}

int loop[MAXN];

int main()
{
	for(int i=2;i<MAXN;i++)
	{
		int a=0,b=1,c;
		for(int j=2;;j++)
		{
			c=(a+b)%i;
			a=b;b=c;
			if(a==0&&b==1)
			{
				loop[i]=j-1;
				break;
			}
		}
		//printf("%d ",loop[i]);
	}
	
	int T;
	scanf("%d",&T);
	while(T--)
	{
		unsigned long long a,b;
		int n;
		scanf("%llu%llu%d",&a,&b,&n);
		if(n==1)
		{
			puts("0");
			continue;
		}
		a%=loop[n];
		a=PowMod(a,b,loop[n]);
		if(a==0)puts("0");
		else if(a==1)puts("1");
		else
		{
			int x=0,y=1,z;
			for(unsigned int i=2;i<=a;i++)
			{
				z=(x+y)%n;
				x=y;y=z;
			}
			printf("%d\n",z);
		}
	}
	
	return 0;
}
