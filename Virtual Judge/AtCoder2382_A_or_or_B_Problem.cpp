#include<cstdio>

long long A,B;

int main()
{
	scanf("%lld%lld",&A,&B);
	long long p=-1LL,q=-1LL;
	for(int i=59;i>=0;i--)
		if((A&(1LL<<i))!=(B&(1LL<<i)))
		{
			p=i;
			break;
		}
	if(p==-1LL)
		puts("1");
	else
	{
		long long L1LL=A&((1LL<<p)-1LL),R1LL=(1LL<<p)+(B&((1LL<<p)-1LL)),L2,R2;
		for(int i=p-1LL;i>=0;i--)
			if(B&(1LL<<i))
			{
				q=i;
				break;
			}
		if(q!=-1LL)
			R1LL=(1LL<<p)+(1LL<<(q+1LL))-1LL;
		L2=(1LL<<p)+(A&((1LL<<p)-1LL));
		R2=(1LL<<(p+1LL))-1LL;
		long long ans;
		if(L2>R1LL)
			ans=R2-L2+1LL+R1LL-L1LL+1LL;
		else
			ans=R2-L1LL+1LL;
		printf("%lld\n",ans);
	}
	
	return 0;
}
