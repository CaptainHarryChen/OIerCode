#include<cstdio>

int main()
{
	unsigned int n,test=0;
	while(scanf("%u",&n)!=EOF)
	{
		if(n==0)
			break;
		test++;
		if(n==1)
		{
			printf("Case %d: 2\n",test);
			continue;
		}
		unsigned int ans=0,tmp=0,cnt=0;
		for(unsigned int i=2;i*i<=n;i++)
			if(n%i==0)
			{
				cnt++;
				tmp=1;
				while(n%i==0)
					n/=i,tmp*=i;
				ans+=tmp;
			}
		if(n!=1)
			ans+=n,cnt++;
		if(cnt==1)
			ans++;
		printf("Case %d: %u\n",test,ans);
	}
	
	return 0;
}
