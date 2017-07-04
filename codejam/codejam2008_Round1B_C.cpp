#include<cstdio>
#define MAXK 1000005
#define MAXN 105
int Q[MAXN],ans[MAXN];
int main()
{
	int T,K,n;
	scanf("%d",&T);
	for(int Case=1;Case<=T;Case++)
	{
		scanf("%d%d",&K,&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",Q+i);
			ans[i]=0;
		}
		for(int i=1,pos=0;i<=K;i++)
		{
			pos=(pos+i-1)%(K-(i-1));
			for(int j=1;j<=n;j++)
				if(!ans[j])
				{
					if(Q[j]==pos+1)
						ans[j]=i;
					else if(Q[j]>pos+1)
						Q[j]--;
				}
		}
		printf("Case #%d:",Case);
		for(int i=1;i<=n;i++)
			printf(" %d",ans[i]);
		printf("\n");
	}
	return 0;
}
