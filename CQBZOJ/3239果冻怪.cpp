#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
const long long P=1000000007;
#define MAXN 100005
int n,T,w;
long long num[MAXN];
long long gcd(long long a,long long b,long long &x,long long &y)
{
	if(b==0)
	{x=1;y=0;return a;}
	long long g;
	g=gcd(b,a%b,y,x);
	y-=a/b*x;
	return g;
}
long long niyuan(long long x,long long p)
{
	long long tx,ty;
	if(gcd(x,p,tx,ty)!=1)return -1;
	while(tx<0)tx+=p;
	return tx;
}
void make_num()
{
	num[0]=1;
	for(long long j=1;j<T;j++)
		num[j]=(((long long)num[j-1]*(T-j+1)%P)*niyuan((long long)j,P))%P;
	num[T]=1;
}
int main()
{
	scanf("%d%d%d",&n,&T,&w);
	int ans=0;
	make_num();
	for(int i=1,a,b;i<=n;i++)
	{
		scanf("%d%d",&a,&b);
		if(abs(w-a)<=T&&abs(w-a)%2==(T%2))
			ans=(int)((ans+((long long)((long long)num[(w-a)/2+T/2]*b))%P)%P);
	}
	printf("%d\n",ans);
	return 0;
}
