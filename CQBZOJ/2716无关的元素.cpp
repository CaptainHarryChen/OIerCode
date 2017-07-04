#include<cstdio>
#include<cstring>
#include<cmath>
#define MAXN 100010
int n,m,prime[MAXN],p=1,c[MAXN],e[MAXN];
int vis[MAXN];
int main()
{
	scanf("%d%d",&n,&m);
	int s=sqrt(m)+0.5;
	for(int i=2;i<=s;i++)
	{
		if(m%i==0)
			prime[p++]=i;
		while(m%i==0)
			{e[p-1]++;m/=i;}
	}
	if(m!=1)
	{prime[p]=m;e[p++]++;}
	bool flag=0;
	for(int i=1;i<n;i++)
	{
		int a=n-i,b=i;
		bool f=1;
		for(int j=1;j<p;j++)
		{
			while(a%prime[j]==0)a/=prime[j],c[j]++;
			while(b%prime[j]==0)b/=prime[j],c[j]--;
		}
		for(int j=1;j<p;j++)
			if(e[j]>c[j])
			{f=0;break;}
		if(f)
		{printf("%d\n",i+1);flag=1;}
	}
	if(!flag)
		printf("0\n");
	return 0;
}
