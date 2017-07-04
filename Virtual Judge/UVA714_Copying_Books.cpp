#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
#define MAXN 505
long long T,n,k,num[MAXN];
bool ans[MAXN];
int main()
{
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld%lld",&n,&k);
		long long l=0,r=0,mid,g,s;
		for(long long i=1;i<=n;i++)
		{
			scanf("%lld",&num[i]);
			l=max(num[i],l);
			r+=num[i];
		}
		memset(ans,0,sizeof ans);
		while(l<r)
		{
			mid=(l+r)/2;
			g=1;s=0;
			for(long long i=n;i>0;i--)
				if(s+num[i]>mid)
				{
					g++;
					s=num[i];
				}
				else
					s+=num[i];
			if(g<=k)
				r=mid;
			else
				l=mid+1;
		}
		g=1;s=0;
		for(long long i=n;i>0;i--)
		{
			if(s+num[i]>l)
			{
				g++;
				s=num[i];
				ans[i]=1;
			}
			else
				s+=num[i];
		}
		for(long long i=1;i<=n&&g<k;i++)
			if(!ans[i])
			{
				ans[i]=1;
				g++;
			}
		for(long long i=1;i<n;i++)
		{
			printf("%lld ",num[i]);
			if(ans[i])
				printf("/ ");
		}
		printf("%lld\n",num[n]);
	}
	return 0;
}
