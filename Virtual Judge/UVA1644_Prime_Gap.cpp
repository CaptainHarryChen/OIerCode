#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=1300000;

int prime[MAXN],pcnt;
bool npr[MAXN];

int main()
{
	npr[1]=true;
	for(int i=2;i<MAXN;i++)
	{
		if(!npr[i])
			prime[++pcnt]=i;
		for(int j=1;j<=pcnt&&1LL*prime[j]*i<MAXN;j++)
		{
			npr[i*prime[j]]=true;
			if(i%prime[j]==0)
				break;
		}
	}
	
	int n;
	for(;;)
	{
		scanf("%d",&n);
		if(n==0)
			break;
		if(!npr[n])
			puts("0");
		else
		{
			int p=lower_bound(prime+1,prime+pcnt+1,n)-prime;
			printf("%d\n",prime[p]-prime[p-1]);
		}
	}
	
	return 0;
}
