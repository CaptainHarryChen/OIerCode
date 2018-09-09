#include<cstdio>

int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int L,U,best=0,bestnum=0;
		scanf("%d%d",&L,&U);
		for(int i=L;i<=U;i++)
		{
			int t=i,cnt=1;
			for(int j=2;1LL*j*j<=t;j++)
				if(t%j==0)
				{
					int k=0;
					while(t%j==0)
						t/=j,k++;
					cnt*=(k+1);
				}
			if(t!=1)
				cnt*=2;
			if(cnt>best)
			{
				best=cnt;
				bestnum=i;
			}
		}
		printf("Between %d and %d, %d has a maximum of %d divisors.\n",L,U,bestnum,best);
	}
	return 0;
}
