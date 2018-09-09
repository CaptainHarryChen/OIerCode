#include<cstdio>
#include<algorithm>
using namespace std;

int main()
{
	int a,b;
	for(;;)
	{
		scanf("%d%d",&a,&b);
		if(a==0&&b==0)
			break;
		long long ans=1;
		for(int i=1;i<=a;i++)
		{
			int phi=i,t=i;
			for(int j=2;j*j<=t;j++)
				if(t%j==0)
				{
					phi=phi/j*(j-1);
					while(t%j==0)
						t/=j;
				}
			if(t!=1)
				phi=phi/t*(t-1);
			ans+=1LL*(b/i)*phi;
			int m=b%i;
			for(int j=1;j<=m;j++)
				if(__gcd(i,j)==1)
					ans++;
		}
		printf("%.7f\n",(4.0*ans)/(1.0*(2*a+1)*(2*b+1)-1));
	}
	return 0;
}
