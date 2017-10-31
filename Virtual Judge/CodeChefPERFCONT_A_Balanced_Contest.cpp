#include<cstdio>
int main()
{
	int T,N,P,a,b,c;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&N,&P);
		a=0;b=0;
		for(int i=1;i<=N;i++)
		{
			scanf("%d",&c);
			a+=(c>=(P/2));
			b+=(c<=(P/10));
		}
		if(a==1&&b==2)
			puts("yes");
		else
			puts("no");
	}
	return 0;
}
