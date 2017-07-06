#include<cstdio>
#define MAXN 100005
int N,M,mon[MAXN];
int main()
{
	while(~scanf("%d%d",&N,&M))
	{
		int L=0,R=0;
		for(int i=1;i<=N;i++)
		{
			scanf("%d",mon+i);
			if(mon[i]>L)L=mon[i];
			R+=mon[i];
		}
		int mid,cnt,sum;
		while(L<R)
		{
			mid=(L+R)>>1;
			cnt=1;sum=0;
			for(int i=1;i<=N&&cnt<=M;i++)
				if(sum+mon[i]>mid)
					cnt++,sum=mon[i];
				else
					sum+=1*mon[i];
			if(cnt>M)
				L=mid+1;
			else
				R=mid-1;
		}
		printf("%d\n",L);
	}
	return 0;
}
