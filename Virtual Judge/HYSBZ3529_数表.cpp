#include<cstdio>
#include<algorithm>
using namespace std;
#define MAXN 100005
#define MAXQ 20005
int mu[MAXN],prime[MAXN],tot;
struct IN{int n,m,a,id;}in[MAXQ];
bool cmp(IN x,IN y){return x.a<y.a;}
bool not_prime[MAXN];
int ans[MAXQ],sum[MAXN];
pair<int,int>f[MAXN];
int bit[MAXN];
void modify(int a,int b)
{
	for(;a<MAXN;a+=(a&(-a)))
		sum[a]+=b;
}
int getsum(int a)
{
	int ret=0;
	for(;a>0;a-=(a&(-a)))
		ret+=sum[a];
	return ret;
}
int solve(int a,int b)
{
	if(a>b)swap(a,b);
	int last=0;
	int ret=0;
	for(int i=1;i<=a;i=last+1)
	{
		last=min(a/(a/i),b/(b/i));
		ret+=(a/i)*(b/i)*(getsum(last)-getsum(i-1));
	}
	return ret;
}
int main()
{
	mu[1]=1;
	for(int i=2;i<MAXN;i++)
	{
		if(!not_prime[i])
		{
			prime[++tot]=i;
			mu[i]=-1;
		}
		for(int j=1;j<=tot&&i*prime[j]<MAXN;j++)
		{
			not_prime[i*prime[j]]=1;
			if(i%prime[j]==0)
			{
				mu[i*prime[j]]=0;
				break;
			}
			mu[i*prime[j]]=-mu[i];
		}
	}
	for(int i=1;i<MAXN;i++)
		for(int j=i;j<MAXN;j+=i)
			f[j].first+=i;
	for(int i=1;i<MAXN;i++)f[i].second=i;
	sort(f+1,f+MAXN);
	int cas;
	scanf("%d",&cas);
	for(int i=1;i<=cas;i++)
	{
		scanf("%d%d%d",&in[i].n,&in[i].m,&in[i].a);
		in[i].id=i;
	}
	sort(in+1,in+cas+1,cmp);
	for(int c=1,i=1;c<=cas;c++)
	{
		for(;i<MAXN&&f[i].first<=in[c].a;i++)
			for(int j=f[i].second;j<MAXN;j+=f[i].second)
				modify(j,f[i].first*mu[j/f[i].second]);
		ans[in[c].id]=solve(in[c].n,in[c].m)&0x7FFFFFFF;
	}
	for(int i=1;i<=cas;i++)
		printf("%d\n",ans[i]);
	return 0;
}
