#include<cstdio>
const int MAXN=1000010;

int prime[MAXN],pcnt;
bool nhp[MAXN],hhp[MAXN];
int ans[MAXN];

int main()
{
	nhp[1]=true;
	for(int i=5;i<MAXN;i+=4)
	{
		if(!nhp[i])
			prime[++pcnt]=i;
		for(int j=1;j<=pcnt&&i*prime[j]<MAXN;j++)
		{
			nhp[i*prime[j]]=true;
			if(!nhp[i])
				hhp[i*prime[j]]=true;
			if(i%prime[j]==0)
				break;
		}
	}
	for(int i=1;i<=MAXN;i++)
		ans[i]=ans[i-1]+hhp[i];
	int h;
	for(;;)
	{
		scanf("%d",&h);
		if(h==0)
			break;
		printf("%d %d\n",h,ans[h]);
	}
	
	return 0;
}
