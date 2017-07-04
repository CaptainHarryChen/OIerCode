#include<cstdio>
#include<cstring>
#define MAXN 125
int c1[MAXN],c2[MAXN];
int main()
{
	int n;
	while(~scanf("%d",&n))
	{
		for(int i=0;i<=n;i++)
			c1[i]=1;
		for(int i=2;i<=n;i++)
		{
			memset(c2,0,sizeof c2);
			for(int j=0;j<=n;j++)
				for(int k=0;k+j<=n;k+=i)
					c2[j+k]+=c1[j];
			memcpy(c1,c2,sizeof c1);
		}
		printf("%d\n",c1[n]);
	}
	return 0;
}
