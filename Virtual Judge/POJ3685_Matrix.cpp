#include<cstdio>
const long long MAXN=50005LL;
int main()
{
	long long T,N,l,r,mid,sum;
	long long M,L,R,Mid,cnt;
	scanf("%I64d",&T);
	while(T--)
	{
		scanf("%I64d%I64d",&N,&M);
		L=-1000000000000LL;
		R=1000000000000LL;
		while(L<R)
		{
			Mid=(L+R+1LL)>>1LL;
			cnt=0LL;
			for(long long j=1LL;j<=N;j++)
			{
				l=1LL,r=N;
				while(l<=r)
				{
					mid=(l+r)>>1LL;
					sum=1LL*mid*mid+100000LL*mid+1LL*j*j-100000LL*j+1LL*mid*j;
					if(Mid<sum)
						r=mid-1LL;
					else
						l=mid+1LL;
				}
 				cnt+=1LL*l-1LL;
			}
			if(cnt<M)
				L=Mid;
			else
				R=Mid-1LL;
		}
		printf("%I64d\n",L+1LL);
	}
	return 0;
}
