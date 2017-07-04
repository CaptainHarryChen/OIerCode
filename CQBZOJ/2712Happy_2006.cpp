#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
#define MAXN 1000010
int m,K,num[MAXN],p[83920],p_c;
bool f[MAXN],fp[MAXN];
void get_prime()
{
	for(int i=2;i<=MAXN;i++)
		if(!fp[i])
		{
			p[++p_c]=i;
			for(long long j=(long long)i*i;j<=MAXN;j+=i)
				fp[j]=1;
		}
}
int gcd(int a,int b)
{
	if(b==0)return a;
	return gcd(b,a%b);
}
int solve(int m)
{
	int n=m;
	int ruler=m;
	for(int i=1;p[i]<=n;i++)
		if(!(n%p[i]))
		{
			ruler=ruler/p[i]*(p[i]-1);
			while(n%p[i]==0)
				n/=p[i];
			for(int j=p[i];j<=m;j+=p[i])
				f[j]=1;
		}
	return ruler;
}
int find(int x)
{
	for(int i=1;i<=m;i++)
	{
		x-=(!f[i]);
		if(x<=0)
			return i;
	}
	return -1;
}
int main()
{
	get_prime();
	while(~scanf("%d%d",&m,&K))
	{
		memset(f,0,sizeof f);
		int ruler=solve(m);
		printf("%d\n",(K-1)/ruler*m+find((K-1)%ruler+1));
	}
	return 0;
}
