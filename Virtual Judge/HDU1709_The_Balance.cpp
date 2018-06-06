#include<cstdio>
#include<cstring>
const int MAXN=205,MAXW=10005;
int W,c1[MAXW],c2[MAXW];
int A[MAXN];
int main()
{
	int n;
	while(scanf("%d",&n)!=EOF)
	{
		W=0;
		for(int i=1;i<=n;i++)
		{
			scanf("%d",A+i);
			W+=A[i];
			A[n+i]=-A[i];
		}
		memset(c1,0,sizeof c1);
		c1[0]=1;
		for(int i=1;i<=2*n;i++)
		{
			memset(c2,0,sizeof c2);
			for(int j=0;j<=W;j++)
			{
				c2[j]+=c1[j];
				if(j+A[i]<=W&&j+A[i]>=0)
					c2[j+A[i]]+=c1[j];
			}
			memcpy(c1,c2,sizeof c1);
		}
		int cnt=0;
		for(int i=0;i<W;i++)
			if(c1[i]==0)
				cnt++;
		printf("%d\n",cnt);
		for(int i=0;i<=W;i++)
			if(c1[i]==0)
				printf("%d%c",i,(--cnt)==0?'\n':' ');
	}
	return 0;
}
