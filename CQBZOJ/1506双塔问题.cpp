#include<cstdio>
#include<iostream>
#include<cstring>
#define MAXN 105
using  namespace std;
int f[MAXN][10*MAXN],h[MAXN],n;
int main()
{
	scanf("%d",&n);
	int sum=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&h[i]);
		sum+=h[i];
	}
	sum/=2;
	memset(f,-1,sizeof f);
	for(int i=1;i<=n;i++)
	{f[i][h[i]]=0;f[i][0]=0;}
	for(int i=2;i<=n;i++)
		for(int j=0;j<=sum;j++)
		{
			f[i][j]=max(f[i-1][j],f[i][j]);//不选第i个水晶
			if(j+h[i]<=sum&&f[i-1][j+h[i]]!=-1)
				f[i][j]=max(f[i-1][j+h[i]]+h[i],f[i][j]);//放上矮塔，还是矮塔
			if(h[i]>j&&f[i-1][h[i]-j]!=-1)
				f[i][j]=max(f[i-1][h[i]-j]+h[i]-j,f[i][j]);//放上矮塔，变为高塔
			f[i][j]=max(f[i-1][j-h[i]],f[i][j]);//放上高塔
		}
	int maxf=0;
	for(int i=1;i<=n;i++)
		maxf=max(f[i][0],maxf);
	if(maxf==0||maxf==-1)
		printf("Impossible\n");
	else
		printf("%d\n",maxf);
	return 0;
}
