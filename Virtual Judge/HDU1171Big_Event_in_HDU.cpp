#include<cstdio>
#include<cstring>
#define MAXN 55
#define MAXM 105
int c1[MAXN*MAXN*MAXM],c2[MAXN*MAXN*MAXM];
int V[MAXN],cnt[MAXN];
int main()
{
	int n,sum;
	while(~scanf("%d",&n))
	{
		if(n<0)break;
		sum=0;
		for(int i=1;i<=n;i++)
		{
			scanf("%d%d",&V[i],&cnt[i]);
			sum+=V[i]*cnt[i];
		}
		memset(c1,0,sizeof c1);
		for(int i=0;i<=cnt[1]*V[1];i+=V[1])
			c1[i]=1;
		int len=V[1]*cnt[1];
		for(int i=2;i<=n;i++)
		{
			memset(c2,0,sizeof c2);
			for(int j=0;j<=len;j++)
				for(int k=0;k<=cnt[i]*V[i];k+=V[i])
					c2[j+k]+=c1[j];
			len+=V[i]*cnt[i];
			memcpy(c1,c2,sizeof c1);
		}
		int ans;
		for(int i=sum/2;i>=0;i--)
			if(c1[i])
			{ans=i;break;}
		printf("%d %d\n",sum-ans,ans);
	}
	return 0;
}
