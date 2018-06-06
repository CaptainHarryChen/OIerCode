#include<cstdio>
#include<cstring>
const int MAXC=305,Z=150;

double pow(double a,int b)
{
	double ret=1;
	while(b)
	{
		if(b&1)
			ret*=a;
		b>>=1;
		a=a*a;
	}
	return ret;
}
double C(int n,int m)
{
	double ret=1;
	for(int i=n;i>n-m;i--)
		ret*=i;
	for(int i=1;i<=m;i++)
		ret/=i;
	return ret;
}

double p[MAXC],p2[MAXC];

int main()
{
	double ans,sum;
	int c,n,m;
	for(;;)
	{
		scanf("%d",&c);
		if(c==0)break;
		scanf("%d%d",&n,&m);
		if(n==0&&m==0)
		{
			puts("1.000");
			continue;
		}
		if(m>n||m>c||(m-n)%2==1)
		{
			puts("0.000");
			continue;
		}
		memset(p,0,sizeof p);
		p[0+Z]=1;
		for(int i=1;i<=m;i++)
		{
			memset(p2,0,sizeof p2);
			for(int k=-c+Z;k<=c+Z;k++)
			{
				p2[k]+=p[k-1]*0.5;
				p2[k]+=-p[k+1]*0.5;
			}
			memcpy(p,p2,sizeof p);
		}
		for(int i=1;i<=c-m;i++)
		{
			memset(p2,0,sizeof p2);
			for(int k=-c+Z;k<=c+Z;k++)
			{
				p2[k]+=p[k-1]*0.5;
				p2[k]+=p[k+1]*0.5;
			}
			memcpy(p,p2,sizeof p);
		}
		
		ans=C(c,m);
		sum=0;
		int flag=(n%2==0?1:-1);
		for(int k=1;k<=c;k++)
			sum+=pow(1.0*k/c,n)*(p[k+Z]+flag*p[-k+Z]);
		ans*=sum;
		printf("%.3lf\n",ans);
	}
	return 0;
}
