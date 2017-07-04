#include<cstdio>
#include<cstring>
#include<algorithm>
using std::min;
#define MAXN 255
#define MAXC 105
int c1[MAXC][MAXN],c2[MAXC][MAXN],W[6]={0,1,5,10,25,50};
int main()
{
	int n=250;
	for(int i=0;i<=min(n,100);i++)
		c1[i][i]=1;
	for(int i=2;i<=5;i++)
	{
		memset(c2,0,sizeof c2);
		for(int p=0;p<=100;p++)
			for(int j=0;j<=n;j++)
				for(int k=0;k*W[i]+j<=n&&p+k<=100;k++)
					c2[p+k][j+k*W[i]]+=c1[p][j];
		memcpy(c1,c2,sizeof c1);
	}
	while(~scanf("%d",&n))
	{
		int ans=0;
		for(int i=0;i<=100;i++)
			ans+=c1[i][n];
		printf("%d\n",ans);
	}
	return 0;
}
