#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=2005;
int mu[MAXN],prime[MAXN/3],pcnt;
int mgcd[MAXN][MAXN];
bool nprime[MAXN];
void Init()
{
	nprime[1]=1;mu[1]=1;
	for(int i=2;i<MAXN;i++)
	{
		if(!nprime[i])
		{
			prime[++pcnt]=i;
			mu[i]=-1;
		}
		for(int j=1;j<=pcnt&&i*prime[j]<MAXN;j++)
		{
			nprime[i*prime[j]]=1;
			if(i%prime[j]==0)
				break;
			mu[i*prime[j]]=-mu[i];
		}
	}
}
int gcd(int a,int b)
{
	if(b==0)
		return a;
	if(mgcd[a][b])
		return mgcd[a][b];
	return mgcd[a][b]=gcd(b,a%b);
}
int f(int x,int g)
{
	int ret=0;
	for(int i=1;i<=x;i++)
		if(gcd(i,g)==1)
			ret+=x/i;
	return ret;
}
int main()
{
	Init();
	int a,b,c;
	scanf("%d%d%d",&a,&b,&c);
	if(b>c)
		swap(b,c);
	int ans=0;
	for(int i=1;i<=a;i++)
		for(int j=1;j<=b;j++)
			if(gcd(i,j)==1)
				ans+=(a/i)*mu[j]*f(b/j,i)*f(c/j,i);
	ans&=1073741823;
	printf("%d\n",ans);
	return 0;
}
