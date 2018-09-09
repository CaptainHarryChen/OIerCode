#include<cstdio>
const int MAXN=50010;

long long phi[MAXN];

int main()
{
	for(int i=2;i<MAXN;i++)
	{
		phi[i]=i;
		int t=i;
		for(int j=2;j*j<=t;j++)
			if(t%j==0)
			{
				phi[i]=phi[i]/j*(j-1);
				while(t%j==0)
					t/=j;
			}
		if(t!=1)
			phi[i]=phi[i]/t*(t-1);
		phi[i]+=phi[i-1];
	}
	
	int n;
	for(;;)
	{
		scanf("%d",&n);
		if(n==0)
			break;
		printf("%lld\n",phi[n]*2LL+1);
	}
	
	return 0;
}
